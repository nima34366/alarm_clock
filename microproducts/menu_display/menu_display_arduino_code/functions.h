
bool buttonpress(bool nval,bool pval){
  if((nval==HIGH) && (pval==LOW)){
    delay(50);
    return true;
  }else{
    return false;
  }
}
