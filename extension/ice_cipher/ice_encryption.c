#include "bindings.h"
#include "ice_encryption.h"
#include "ice.h"

void ice_encryption_deallocate(void* data)
{
	ICE_KEY* key = (ICE_KEY*)data;

	ice_key_destroy(key);
}

VALUE ice_encryption_allocate(VALUE klass)
{
	ICE_KEY* key = ice_key_create(0);

	return Data_Wrap_Struct(klass, NULL, ice_encryption_deallocate, key);
}

void Init_ice_encryption()
{
	VALUE cIceEncryption = rb_define_class_under(kIceModule, "Encryption", rb_cObject);

	rb_define_alloc_func(cIceEncryption, ice_encryption_allocate);
	rb_define_method(cIceEncryption, "initialize", ice_encryption_initialize, 1);
	rb_define_method(cIceEncryption, "key_size", ice_encryption_key_size, 0);
	rb_define_method(cIceEncryption, "block_size", ice_encryption_block_size, 0);
	rb_define_method(cIceEncryption, "key=", ice_encryption_set_key, 1);
	rb_define_method(cIceEncryption, "encrypt", ice_encryption_encrypt, 1);
	rb_define_method(cIceEncryption, "decrypt", ice_encryption_decrypt, 1);
}

VALUE ice_encryption_initialize(VALUE self, VALUE level)
{
	Check_Type(level, T_FIXNUM);

	ice_encryption_create_key(self, NUM2INT(level), NULL);

	return self;
}

void ice_encryption_create_key(VALUE self, int level, unsigned char* key)
{
	// Destroy the current key
	ICE_KEY* ik;

	Data_Get_Struct(self, ICE_KEY, ik);

	if (ik != NULL)
	{
		ice_key_destroy(ik);
	}

	// Create a new key
	ik = ice_key_create(level);

	if (key != NULL)
	{
		// Set an encryption key
		ice_key_set(ik, key);
	}
}

VALUE ice_encryption_key_size(VALUE self)
{
	ICE_KEY* key;

	Data_Get_Struct(self, ICE_KEY, key);

	return INT2NUM(ice_key_key_size(key));
}

VALUE ice_encryption_block_size(VALUE self)
{
	ICE_KEY* key;

	Data_Get_Struct(self, ICE_KEY, key);

	return INT2NUM(ice_key_block_size(key));
}

VALUE ice_encryption_set_key(VALUE self, VALUE value)
{
	ICE_KEY* key;

	Check_Type(value, T_STRING);
	Data_Get_Struct(self, ICE_KEY, key);

	if (key != NULL)
	{
		ice_key_set(key, (unsigned char*)StringValuePtr(value));

		return value;
	}

	return Qnil;
}

VALUE ice_encryption_encrypt(VALUE self, VALUE text)
{
	ICE_KEY*       key;
	VALUE          result;
	unsigned int   textLength;
	unsigned char* plainText;
	unsigned char* cipherText;

	// Get the string length
	textLength = RSTRING_LEN(text);

	// Check that the string is divisible by 8
	if (textLength % 8 != 0)
	{
		rb_raise(rb_eArgError, "expected argument to be divisible by 8, but length is %d", textLength);

		return Qnil;
	}

	// Get the contents of the string
	plainText = (unsigned char*)StringValuePtr(text);

	// Allocate space for the cipher text
	cipherText = (unsigned char*)malloc(textLength);

	// Get the data struct
	Data_Get_Struct(self, ICE_KEY, key);

	// Decrypt the cipher text
	ice_key_encrypt(key, (const unsigned char*)plainText, cipherText);

	if (cipherText != NULL)
	{
		result = rb_str_new((const char*)cipherText, textLength);
	}
	else
	{
		result = Qnil;
	}

	return result;
}

VALUE ice_encryption_decrypt(VALUE self, VALUE text)
{
	ICE_KEY*       key;
	VALUE          result;
	unsigned int   textLength;
	unsigned char* plainText;
	unsigned char* cipherText;

	// Get the string length
	textLength = RSTRING_LEN(text);

	// Check that the string is divisible by 8
	if (textLength % 8 != 0)
	{
		rb_raise(rb_eArgError, "expected argument to be divisible by 8, but length is %d", textLength);

		return Qnil;
	}

	// Get the contents of the string
	cipherText = (unsigned char*)StringValuePtr(text);

	// Allocate space for the decrypted text
	plainText = (unsigned char*)malloc(textLength);

	// Get the data struct
	Data_Get_Struct(self, ICE_KEY, key);

	// Decrypt the cipher text
	ice_key_decrypt(key, (const unsigned char*)cipherText, plainText);

	if (plainText != NULL)
	{
		result = rb_str_new((const char*)plainText, textLength);
	}
	else
	{
		result = Qnil;
	}

	return result;
}