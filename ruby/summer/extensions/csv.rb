require 'csv'

result = ["1st", "2nd", "3rd", "asdfasdf"]

CSV.open("exit.csv", "wb") do |csv|
	csv << result
end
