#include "layer.h"

layer::layer() {}

layer::~layer() {}
void layer::mousePressEvent(QMouseEvent *event) { emit clicked(); }
