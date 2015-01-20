require_relative './program.rb'

describe "#Burger" do
	
	before :each do
		@burger = Burger.new "a", "b", "c"
	end
	it "makes a new burger" do
		@burger = Burger.new "a", "b", "c"
	end
	it "takes new arguments" do
		@burger.add "d"
	end
	it "kills arg in burger" do
		expect(@burger.a).not_to be(nil)
		@burger.remove "a"
		expect(@burger.a).to be(nil)
	end
end
