class Book
	attr_reader :name, :size, :author
	def initialize (name = nil, size = nil, author = nil)
		@name=name
		@size=size
		@author=author
	end
end
