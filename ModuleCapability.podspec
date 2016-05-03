#
# Be sure to run `pod lib lint ModuleCapability.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "ModuleCapability"
  s.version          = "0.1.0"
  s.summary          = "This is a configureation of module capability."

  s.homepage         = "https://git.musjoy.com:ModuleCapability"
  s.license          = 'MIT'
  s.author           = { "Raymond" => "Ray.musjoy@gmail.com" }
  s.source           = { :git => "git@git.musjoy.com:ModuleCapability.git", :tag => "v-#{spec.version}" }

  s.ios.deployment_target = '7.0'

  s.source_files = 'ModuleCapability/Classes/**/*'

end
