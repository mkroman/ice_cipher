#ifndef __RUBY_ICE_KEY_H
#define __RUBY_ICE_KEY_H
#include <ruby.h>

void Init_ice_encryption();

void ice_encryption_create_key(VALUE self, int level, unsigned char* key);
void ice_encryption_deallocate(void *ik);
VALUE ice_encryption_allocate(VALUE klass);
VALUE ice_encryption_initialize(VALUE self, VALUE level);
VALUE ice_encryption_set_key(VALUE self, VALUE key);
VALUE ice_encryption_key_size(VALUE self);
VALUE ice_encryption_block_size(VALUE self);
VALUE ice_encryption_encrypt(VALUE self, VALUE text);
VALUE ice_encryption_decrypt(VALUE self, VALUE ciphertext);

#endif