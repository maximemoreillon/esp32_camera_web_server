/* 
 *  Most of the code here based on me-no-dev's work
 *  This guy is a legend
 *  https://gist.github.com/me-no-dev/d34fba51a8f059ac559bf62002e61aa3
 */
 
typedef struct {
  camera_fb_t * fb;
  size_t index;
} camera_frame_t;

#define PART_BOUNDARY "123456789000000000000987654321"
#define JPG_CONTENT_TYPE "image/jpeg"

static const char* STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* STREAM_PART = "Content-Type: %s\r\nContent-Length: %u\r\n\r\n";

class AsyncFrameResponse: public AsyncAbstractResponse {
 
  private:
    camera_fb_t * fb;
    size_t _index;
        
  public:
    AsyncFrameResponse(camera_fb_t * frame, const char * contentType){
      _callback = nullptr;
      _code = 200;
      _contentLength = frame->len;
      _contentType = contentType;
      _index = 0;
      fb = frame;
    }
      
    ~AsyncFrameResponse(){
      // EXPERIMENT FROM HERE
      Serial.println("GOODBYE AsyncFrameResponse");
      esp_camera_fb_return(fb);
      fb = nullptr;
      // EXPERIMENT TO HERE

      
      // Destructor: clears frame buffer
//      if(fb != nullptr) {
//        Serial.println("GOODBYE FRAME BUFFER");
//        esp_camera_fb_return(fb);
//      }
    }
    
    bool _sourceValid() const { 
      return fb != nullptr;
    }
      
    virtual size_t _fillBuffer(uint8_t *buf, size_t maxLen) override{
      size_t ret = _content(buf, maxLen, _index);
      if(ret != RESPONSE_TRY_AGAIN) _index += ret;
      return ret;
    }
      
    size_t _content(uint8_t *buffer, size_t maxLen, size_t index){
      memcpy(buffer, fb->buf+index, maxLen);

      // clear frame buffer
      if((index+maxLen) == fb->len){
        esp_camera_fb_return(fb);
        fb = nullptr;
      }
      
      return maxLen;
    }
};

class AsyncJpegStreamResponse: public AsyncAbstractResponse {
  private:
    camera_frame_t _frame;
    size_t _index;
      
  public:
    AsyncJpegStreamResponse(){
      // constructor
      _callback = nullptr;
      _code = 200;
      _contentLength = 0;
      _contentType = STREAM_CONTENT_TYPE;
      _sendContentLength = false;
      _chunked = true;
      _index = 0;
      memset(&_frame, 0, sizeof(camera_frame_t));
    }
      
    ~AsyncJpegStreamResponse(){
      // Destructor: Clear frame buffer
      if(_frame.fb) esp_camera_fb_return(_frame.fb);
    }
    bool _sourceValid() const {
      // Seems a bit pointless but provably overrides parent class
      return true;
    }
      
    virtual size_t _fillBuffer(uint8_t *buf, size_t maxLen) override {
      size_t ret = _content(buf, maxLen, _index);
      if(ret != RESPONSE_TRY_AGAIN)_index += ret;
      return ret;
    }
      
    size_t _content(uint8_t *buffer, size_t maxLen, size_t index){

      if(!_frame.fb || _frame.index == _frame.fb->len){

          if(index && _frame.fb){
              // clear frame buffer
              esp_camera_fb_return(_frame.fb);
              _frame.fb = NULL;
          }



          // Check for header lengths
          if(maxLen < (strlen(STREAM_BOUNDARY) + strlen(STREAM_PART) + strlen(JPG_CONTENT_TYPE) + 8)){
            log_w("Not enough space for headers");
            return RESPONSE_TRY_AGAIN;
          }
          
          // get frame
          _frame.index = 0;
          _frame.fb = esp_camera_fb_get();

          // Check if frame was taken successfully
          if (_frame.fb == NULL) {
            log_e("Camera frame failed");
            return 0;
          }


          //send boundary
          size_t boundary_length = 0;
          if(index){
            boundary_length = strlen(STREAM_BOUNDARY);
            memcpy(buffer, STREAM_BOUNDARY, boundary_length);
            buffer += boundary_length;
          }
          
          //send header
          size_t headers_length = sprintf((char *)buffer, STREAM_PART, JPG_CONTENT_TYPE, _frame.fb->len);
          buffer += headers_length;
          
          //send frame
          headers_length = maxLen - headers_length - boundary_length;
          if(headers_length > _frame.fb->len){
            maxLen -= headers_length - _frame.fb->len;
            headers_length = _frame.fb->len;
          }
          memcpy(buffer, _frame.fb->buf, headers_length);
          _frame.index += headers_length;
          return maxLen;
      }

      size_t available = _frame.fb->len - _frame.index;
      if(maxLen > available){
        maxLen = available;
      }
      memcpy(buffer, _frame.fb->buf+_frame.index, maxLen);
      _frame.index += maxLen;

      return maxLen;
    }
};




void sendJpg(AsyncWebServerRequest *request){
  Serial.println("[HTTP] /frame requested");
  
  camera_fb_t * fb = esp_camera_fb_get();

  if (fb == NULL) {
    log_e("Camera frame failed");
    request->send(501);
    return;
  }

  // Note: Images are in JPEG because camera configured as such in camera.ino
  AsyncFrameResponse * response = new AsyncFrameResponse(fb, JPG_CONTENT_TYPE);
  
  
  
  if (response == NULL) {
    log_e("Response alloc failed");
    request->send(501);
    return;
  }
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
  return;

}



void streamJpg(AsyncWebServerRequest *request){
  Serial.println("[HTTP] /stream requested");
  AsyncJpegStreamResponse *response = new AsyncJpegStreamResponse();
  
  if(!response){
    request->send(501);
    return;
  }
  
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}


void http_config(){

  Serial.println("[HTTP] Server config");
  

  iot_kernel.http.on("/frame", HTTP_GET, sendJpg);
  iot_kernel.http.on("/stream", HTTP_GET, streamJpg);


}
