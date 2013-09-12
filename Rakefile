require 'rake/extensiontask'
require 'rspec/core/rake_task'

Rake::ExtensionTask.new 'ice_cipher' do |ext|
  ext.ext_dir = 'extension/ice_cipher'
  ext.lib_dir = 'library/ice-cipher'
end

RSpec::Core::RakeTask.new :spec => [:compile] do
end

task default: :spec