require 'simplecov'
SimpleCov.start
require_relative 'script.rb'

describe "#reopen_folder" do
	it "Enters the reopen_folder function" do
		reopen_folder("../")
	end
end
describe "Wrong number of arguments" do
	it "Has 0/1 arguments" do
		ARGV[0] = nil
		main
	end
end
