// HAL

// HAL - trim
double _cliGetHALTrim(leg &_leg, int angleId) {
  return radToDeg(getHALTrim(_leg, angleId));
}

double cliGetHALTrimLFAlpha(double id) {
  return _cliGetHALTrim(legs[LEGLF], ALPHA);
}
double cliGetHALTrimLFBeta(double id) {
  return _cliGetHALTrim(legs[LEGLF], BETA);
}
double cliGetHALTrimLFGamma(double id) {
  return _cliGetHALTrim(legs[LEGLF], GAMMA);
}
double cliGetHALTrimRFAlpha(double id) {
  return _cliGetHALTrim(legs[LEGRF], ALPHA);
}
double cliGetHALTrimRFBeta(double id) {
  return _cliGetHALTrim(legs[LEGRF], BETA);
}
double cliGetHALTrimRFGamma(double id) {
  return _cliGetHALTrim(legs[LEGRF], GAMMA);
}
double cliGetHALTrimLHAlpha(double id) {
  return _cliGetHALTrim(legs[LEGLH], ALPHA);
}
double cliGetHALTrimLHBeta(double id) {
  return _cliGetHALTrim(legs[LEGLH], BETA);
}
double cliGetHALTrimLHGamma(double id) {
  return _cliGetHALTrim(legs[LEGLH], GAMMA);
}
double cliGetHALTrimRHAlpha(double id) {
  return _cliGetHALTrim(legs[LEGRH], ALPHA);
}
double cliGetHALTrimRHBeta(double id) {
  return _cliGetHALTrim(legs[LEGRH], BETA);
}
double cliGetHALTrimRHGamma(double id) {
  return _cliGetHALTrim(legs[LEGRH], GAMMA);
}
