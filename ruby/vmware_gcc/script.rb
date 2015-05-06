require "net/http"
require "uri"

def format_objects(string)
	hash = Hash.new
	temp = string.split(' ')
	for i in (0..(temp.size)-1).step(2) do
		if(hash.has_key?(temp[i]))
			arr = Array.new
			arr << hash[temp[i]]
			arr << temp[i+1]
			hash[temp[i]] = arr.flatten
		else
			hash[temp[i]] = temp[i+1]
		end
	end
	return hash
end

def format_roots(string)
	return string.split(' ')
end

def root_protect(root)
	temp = $objects[root]
	$objects.delete(root)
	if ("#{temp.class}" == "NilClass")
		return
	elsif ("#{temp.class}" == "String")
		root_protect($objects[temp])
		$objects.delete(temp)
	else
		temp.each do |i|
			root_protect(i)
			$objects.delete(i)
		end
	end
end

def object_clean(object)
	uri = URI("http://192.168.0.114:8080/api/sector/#{ARGV[0]}/company/vbgf/trajectory")
	res = Net::HTTP.post_form(uri, "trajectory" => "#{object}")
end

$roots = Net::HTTP.get(URI.parse("http://192.168.0.114:8080/api/sector/#{ARGV[0]}/roots"))
$objects = Net::HTTP.get(URI.parse("http://192.168.0.114:8080/api/sector/#{ARGV[0]}/objects"))
$roots = format_roots($roots)
$objects = format_objects($objects)

while(!$roots.empty?) do
	if ("#{$objects[$roots[0]].class}" == "String")
		root_protect($objects[$roots[0]])
	else
		$objects[$roots[0]].each do |i|
			root_protect(i)
		end
	end
	$objects.delete($roots[0])
	$roots.delete_at(0)
end

puts "Number of obj to be removed: "
puts $objects.count

while(!$objects.empty?) do
	$objects.each_key do |i|
		puts i
		object_clean(i)
		$objects.delete(i)
	end
end

puts "Done!"




#Old implementation with arrays,
#the new one executes a hash for faster seek times
#def format_objects(string)
#	pair = Array.new(2, 0)
#	arr = Array.new(0, pair)
#	temp = string.split(' ')
#	for i in (0..(temp.size)-1).step(2) do
#		pair[0] = temp[i]
#		pair[1] = temp[i+1]
#		arr[i/2] = pair[0..1]
#	end
#	return arr
#end

#def arr_to_hash (array)
#	arr = array.to_s.split(' ')
#	hash = Hash.new
#	for i in (0..(arr.size)-1).step(2) do
#		hash[arr[i]] = arr[i+1]
#	end
#	return hash
#end

#hashes = Array.new
#for i in 0..10 do
#	hashes[i] = arr_to_hash(objects[i])
#end
#puts hash[3]

# Will print response.body
#Net::HTTP.get_print(objects[2])
#puts objects[2]

#uri = URI("http://192.168.0.114:8080/api/sector/5/company/vbgf/trajectory")
#res = Net::HTTP.post_form(uri, "trajectory" => "8")
#puts res.body
