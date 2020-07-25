// HAL
// HAL - trim

bool _cliSetHALTrim (leg &_leg, int angleId, double deg) {
  return setHALTrim(_leg, angleId, deg);
}

double _cliSetHALTrimError()
{
  cliError("Out of limit");

  return 0;
}

double cliSetHALTrimLFAlpha(double deg) {
  if (_cliSetHALTrim (legs[LEGLF], ALPHA, deg)) {
    return _cliGetHALTrim(legs[LEGLF], ALPHA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimLFBeta(double deg) {
  if (_cliSetHALTrim (legs[LEGLF], BETA, deg)) {
    return _cliGetHALTrim(legs[LEGLF], BETA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimLFGamma(double deg) {
  if (_cliSetHALTrim (legs[LEGLF], GAMMA, deg)) {
    return _cliGetHALTrim(legs[LEGLF], GAMMA);
  }

  return _cliSetHALTrimError();
}


double cliSetHALTrimRFAlpha(double deg) {
  if (_cliSetHALTrim (legs[LEGRF], ALPHA, deg)) {
    return _cliGetHALTrim(legs[LEGRF], ALPHA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimRFBeta(double deg) {
  if (_cliSetHALTrim (legs[LEGRF], BETA, deg)) {
    return _cliGetHALTrim(legs[LEGRF], BETA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimRFGamma(double deg) {
  if (_cliSetHALTrim (legs[LEGRF], GAMMA, deg)) {
    return _cliGetHALTrim(legs[LEGRF], GAMMA);
  }

  return _cliSetHALTrimError();
}


double cliSetHALTrimLHAlpha(double deg) {
  if (_cliSetHALTrim (legs[LEGLH], ALPHA, deg)) {
    return _cliGetHALTrim(legs[LEGLH], ALPHA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimLHBeta(double deg) {
  if (_cliSetHALTrim (legs[LEGLH], BETA, deg)) {
    return _cliGetHALTrim(legs[LEGLH], BETA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimLHGamma(double deg) {
  if (_cliSetHALTrim (legs[LEGLH], GAMMA, deg)) {
    return _cliGetHALTrim(legs[LEGLH], GAMMA);
  }

  return _cliSetHALTrimError();
}


double cliSetHALTrimRHAlpha(double deg) {
  if (_cliSetHALTrim (legs[LEGRH], ALPHA, deg)) {
    return _cliGetHALTrim(legs[LEGRH], ALPHA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimRHBeta(double deg) {
  if (_cliSetHALTrim (legs[LEGRH], BETA, deg)) {
    return _cliGetHALTrim(legs[LEGRH], BETA);
  }

  return _cliSetHALTrimError();
}

double cliSetHALTrimRHGamma(double deg) {
  if (_cliSetHALTrim (legs[LEGRH], GAMMA, deg)) {
    return _cliGetHALTrim(legs[LEGRH], GAMMA);
  }

  return _cliSetHALTrimError();
}
