require "../ruby/main.rb"
require 'simplecov'
SimpleCov.start

describe "main.rb" do
	it "Checks if i == 0" do
		expect(i).to eq(0)
	end
end
