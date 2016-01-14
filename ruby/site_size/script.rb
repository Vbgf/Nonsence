require 'net/http'

def get_html(link)
	begin
		uri = URI(link)
		res = Net::HTTP.get(uri)
		return res
	rescue
		return 
	end
end

def get_links(html)
	res = {}
	array = html.split('"' + $link_start)
	array.shift
	array.each do |link|
		res[$link_start + link.split('"')[0]] = false
	end
	array = html.split("'" + $link_start)
	array.shift
	array.each do |link|
		res[$link_start + link.split("'")[0]] = false
	end
	return res
end

#$link_start = "http://www.simplesite.com/"
#$link_start = "http://www.SmallSites.com/"
#$link_start = "http://www.planetdolan.com/"
$link_start = "http://www.elsys-bg.org/"

size = 0;
links = {};
new_links = {};

html = get_html($link_start)
links = get_links(html)
links[$link_start] = true
size = size + html.size()

while links.has_value?(false) do
	links.each do |link, visited|
		if(!visited)
			html = get_html(link)
			if(html != nil)
				size = size + html.size()
				new_links.merge!(get_links(html))
				puts "HTML size of #{link}: "
				puts html.size()
			end
			links[link] = true
		end
	end
	links = new_links.merge(links)
	new_links = {}
end

puts "Final size:"
puts size

