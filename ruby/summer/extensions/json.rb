f = File.new("exit.json", "w")
f << "{\n"
f << "\t\"tag1\" : \"Info\", \n"
f << "\t\"tag2\" : \"Info2\", \n"
f << "\t\"new_body\" : {\n"
f << "\t\t\"tag3\": \"Info3\"\n"
f << "\t}\n"
f << "}\n"
f.close
