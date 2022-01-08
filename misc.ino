String get_chip_id(){
  uint32_t chipId = 0;

  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  return String(chipId, HEX);
}

String get_device_name(){
  return String(DEVICE_TYPE) + "-" + get_chip_id();
}
