#!/usr/bin/gem build
# encoding: utf-8

Gem::Specification.new do |spec|
  spec.name     = "ice_cipher"
  spec.version  = "0.1"
  spec.summary  = "ICE encryption library"

  spec.license  = "Internet Systems Consortium (ISC)"
  spec.author   = "Mikkel Kroman"
  spec.email    = "mk@uplink.io"
  spec.files    = Dir["library/**/*.rb", "extension/**/*"]

  spec.add_development_dependency "rspec"
  spec.add_development_dependency "rake-compiler"

  spec.require_path = "library"
  spec.required_ruby_version = ">= 1.9.1"
  spec.extensions = %w[extension/ice_cipher/extconf.rb]
end

# vim: set syntax=ruby:
