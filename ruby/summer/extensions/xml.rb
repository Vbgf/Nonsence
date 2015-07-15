f = File.new("exit.xml", "w")

f << "<script>\n"
f << "\t<tag>\n"
f << "\t\tInfo in first tag here!\n"
f << "\t</tag>\n"
f << "\t<tag>\n"
f << "\t\tInfo in second tag here!\n"
f << "\t</tag>\n"
f << "</script>\n"

f.close
