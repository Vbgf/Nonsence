require 'simplecov'
SimpleCov.start
require_relative 'script.rb'

describe Book do
	it "makes book wit def values" do
		book = Book.new
		expect(book.get_author).to eq("None")
		expect(book.get_pages).to eq(0)
	end
end
