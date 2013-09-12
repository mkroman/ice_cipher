#include "bindings.h"
#include "ice_encryption.h"

VALUE kIceModule = Qnil;

void Init_ice_cipher() {
	kIceModule = rb_define_module("ICE");

	Init_ice_encryption();
}