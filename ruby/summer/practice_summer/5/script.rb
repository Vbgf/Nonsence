class Book
	def initialize (auth = "None", pages = 0)
		@author = auth
		@pages = pages
	end
	def get_author
		@author
	end
	def get_pages
		@pages
	end
end
