require 'csv'

folder = ARGV[0]
array = []
if (File.directory?(folder))
	if(folder[-1] != '/')
		folder = folder + '/'
	end
	Dir.glob("#{folder}*").each do |file|
		if((file.split(folder)[1].split('_')[0].size == 10)and(File.file?(file)))
			array << file
		end
	end

	if(!array.empty?)
		CSV.open("result.csv", "wb") do |csv|
			array.each do |file|
				csv << file.split('/')[-1].split('_').first(2)
			end
		end
	end
end
