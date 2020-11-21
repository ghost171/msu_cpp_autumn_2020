template<class T, class... Args>
void format1(vector<string> &v, const T &input, Args&&... args) {
    stringstream ss;
    ss << input;
    string s;
    std::getline (ss,s);
    v.push_back(s);
    format1(v, std::forward<Args>(args)...);
}

template<class T, class... Args>
string format(const T &input, Args&&... args) {
    vector<string> v;
    format1(v, input, args...);
    string s = v[0];
    int k = 0;
    for (auto i = v.begin() + 1; i < v.end(); i++) {
        string g = *i;
        string h = "{" + to_string(k) + "}";
        while (true) {
            int index = s.find(h, 0);
            if (index == std::string::npos) {
                break;
            }
            s.replace(index, h.size(), g);
            index++;
        }
        k++;
    }
    try{
        for (int i = 0; i < s.size(); i++) {
            string a = "";
            if (s[i] == '{') {
                a += s[i];
                while(i < s.size() || s[i] == '}') {
                    i++;
                    a += s[i]; 
                }
                if (a != "") {
                    throw Error("Error in replacing {}", __FILE__, __LINE__);
                }           
            }
        }
    }
    catch (const Error& error) {
        cout << error.message_ << endl;
    }
    return s;
    
}