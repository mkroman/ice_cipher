#ifndef __RUBY_ICE_KEY_H
#define __RUBY_ICE_KEY_H
#include <ruby.h>

void Init_ice_cipher_class();

void ice_cipher_create_key(VALUE self, int level, unsigned char* key);
void ice_cipher_deallocate(void *ik);
VALUE ice_cipher_allocate(VALUE klass);
VALUE ice_cipher_initialize(VALUE self, VALUE level);
VALUE ice_cipher_set_key(VALUE self, VALUE key);
VALUE ice_cipher_key_size(VALUE self);
VALUE ice_cipher_block_size(VALUE self);
VALUE ice_cipher_encrypt(VALUE self, VALUE text);
VALUE ice_cipher_decrypt(VALUE self, VALUE ciphertext);

#endif
