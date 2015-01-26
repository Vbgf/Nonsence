require 'simplecov'
SimpleCov.start
require_relative 'script.rb'

describe PlaylistItem do
	before :each do
		playlist_item = PlaylistItem.new
	end
	it "makes a new obj" do
		playlist_item = PlaylistItem.new
	end
	it "checks if obj exists" do
		playlist_item = PlaylistItem.new
		expect(playlist_item.exists?).to eq(false)
	end
	it "deletes an id" do
		playlist_item = PlaylistItem.new
		expect(playlist_item.delete).to eq(true)
	end
end
