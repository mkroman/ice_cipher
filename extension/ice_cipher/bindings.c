#include "bindings.h"
#include "ice_cipher.h"

VALUE kIceModule = Qnil;

void Init_ice_cipher() {
	kIceModule = rb_define_module("ICE");

	Init_ice_cipher_class();
}
