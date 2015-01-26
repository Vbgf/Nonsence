require 'simplecov'
SimpleCov.start
require_relative 'script.rb'

describe Book do
	it "makes an empty obj Book" do
		book = Book.new
		expect(book.name).to eq(nil)
		expect(book.size).to eq(nil)
		expect(book.author).to eq(nil)
	end
	it "makes an obj Book with arguments" do
		book = Book.new("name",100,"author")
		expect(book.name).to eq("name")
		expect(book.size).to eq(100)
		expect(book.author).to eq("author")
	end
end
