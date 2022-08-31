    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <map>
    #include <sstream>
    #include <stack>
    #include <stdexcept>
    std::string input;
    void Convert(std::string name){
        std::ifstream f(name);
        if(f.is_open()){
            input = "";
            std::string sentence;
            while(f.good()){
                getline(f,sentence);
                input += sentence;
                input += '\n';
            }
            f.close();
        }else {
            throw std::runtime_error("File error");
        }
    }
    int P(char operation){
        if(operation == '+' || operation == '-'){
            return 1;
        }else if(operation == '*')
            return 2;
        return 0;
    }
    int A(int a, int b, char operation){
        switch(operation){
            case '+':
                return a+b;
            case '-':
                return a-b;
            case '*':
                return a*b;
        }
        return 0;
    }
    int formulate(std::string stre){
        std::string str= stre;
        for(int i = 0; i < str.length();i++){
            if(str[i] == '*' || str[i] == '+' || str[i] == '-'){
                str.insert(i, " ");
                str.insert(i+2, " ");
                i+= 2;
            }
        }
        size_t i= 0;
        std::stack<int> Operands;
        std::stack<char> operations;
        for(i = 0; i < str.length();i++){
            if(str[i] == ' '){
                continue;
            }else if(isdigit(str[i])){
                int val = 0;
                while(i < str.length() && isdigit(str[i])){
                    val = (val*10) + (str[i] - '0');
                    i++;
                }
                Operands.push(val);
            }else {
                while((!operations.empty()) && P(operations.top()) >= P(str[i])){
                    int num2 = Operands.top();
                    Operands.pop();
                    
                    int num1 = Operands.top();
                    Operands.pop();
                    
                    char op = operations.top();
                    operations.pop();
                    
                    Operands.push(A(num1,num2, op));
                }
                operations.push(str[i]);
                }
        }
            while(!operations.empty()) {
                int num2 = Operands.top();
                Operands.pop();
                
                int num1 = Operands.top();
                Operands.pop();
                
                char op = operations.top();
                operations.pop();
                
                Operands.push(A(num1,num2,op));
            }
        return Operands.top();
    }
    std::vector<std::string> tokens;
    std::vector<std::string>Parser(std::string command){
    tokens.clear();
    std::string temporary;
    std::string test;
    int Quotecounter = 0;
    for (size_t i = 0; i < command.length (); ++i)
      {
        // if first term is a comment
        if(command[0] == '#'){
            tokens.push_back(command);
            return tokens;
        }
        //return token after encountering a comment sign and not index 0
        if(command[i] == '#' && i != 0){
            return tokens;
        }
        if(command[i] == '"')
        {
            //finds total amount of quotation marks
            int sum = 0;
            for(size_t h = i; h < command.length();h++){
                if(command[h] == '\"'){
                    sum++;
                }
            }
            // if quotations are more than 2 should be invalid
            if(sum > 2){
                std::vector<std::string> he;
                he.push_back("ERROR");
                return he;
            }
            Quotecounter++;
            //Checks it cannot find a second quote, it return error index
            if(command.find('"',i+1) == std::string::npos){
                std::vector<std::string> r;
                r.push_back("ERROR");
                return r;
            }
            //Assume it will find next quote after passing the above test
            int secondQuote = (int) command.find ('"', i + 1);
            Quotecounter++;
            int nameSize = secondQuote - i - 1;
            //substring's the whole thing
            test = command.substr (i + 1, nameSize);
            tokens.push_back (test);
            test.clear ();
            //Catches up after 2nd quote in the iteration
            i = secondQuote + 1;
            continue;
      }
    // skips spaces & tabs
    if (command[i] == ' ' || command[i] == '\t' || command[i] == '\n'){
        if(test.empty()){
            continue;
        }
        //pushes back whatever it has after encountering a space
        tokens.push_back (test);
        test.clear ();
        continue;
      }
    // Adds the Operations and Assignment
    if(command[i] == '+' || command[i] == '=' || command[i] == '-' || command[i] == '*'){
        std::string op = " ";
        op[0] = command[i];
        tokens.push_back (op);
        op.clear();
        test.clear();
        continue;
      }
    else
      {
        // Checks if the next character is an operator
        if (command[i+1] == '+' || command[i+1] == '=' || command[i+1] == '-' || command[i+1] == '*'){
            test += command[i];
            tokens.push_back(test);
            test.clear();
            continue;
        }
        test += command[i];
        if (i == command.length () - 2)
          {
            tokens.push_back (test);
            test.clear ();
          }
      }
    }
    return tokens;
    }
    bool IsNumber(std::string str){
        for(size_t i = 0; i < str.length();i++){
            if(isdigit(str[0])){
                continue;
            }else{
                return false;
            }
        }
        return true;
    }
    bool IsString(std::string str){
        for(size_t i = 0; i < str.length();i++){
            if(isalpha(str[0])){
                continue;
            }else {
                return false;
            }
        }
        return true;
    }
    std::map<std::string, std::string> Smap;
    std::map<std::string, long long> Nmap;
    bool logic(std::vector<std::string> in, int counter){
        //Turns Line Counter to string for error output
        std::string Line = std::to_string(counter);
        //Skips Lines starting with a comment or empty spaces
        if(in.size() == 0){
            return true;
        }
        //Check if any quotation marks found during parsing
        for(size_t i = 0; i < in.size();i++){
            if(in[i] == "ERROR"){
                return false;
            }
        }
        if(in.size() == 1){
            return true;
        }
        //Handles All Declarations of size 2
        if(in.size() == 2){
            if(in[0] == "STRING"){
                for(int i = 0; i < in[1].length()-1;i++){
                    if(isdigit(in[1][0])){
                        return false;
                    }
                    if(isalnum(in[1][i]) || in[1][i] == '_'){
                        continue;
                    }else {
                            return false;
                    }
                }
                Smap.insert(std::make_pair(in[1],""));
                return true;
                
            }else if(in[0] == "NUMBER"){
                for(int i = 0; i < in[1].length();i++){
                    if((isalnum(in[1][i]) || in[1][i] == '_')&& !isdigit(in[1][0])){
                        continue;
                    }else {
                        return false;
                    }
                }
                Nmap.insert(std::make_pair(in[1],0));
                return true;
            }else if(in[0] == "PRINT"){
                if(in.size() == 2){
                    if(Nmap.size() >= 1){
                        for(auto it=Nmap.begin(); it != Nmap.end(); it++){
                            if(it->first == in[1]){
                                std::cout << it->second;
                                return true;
                            }
                        }
                    }
                    
                    if(Smap.size() >= 1){
                        for(auto it=Smap.begin(); it != Smap.end(); it++){
                            if(it->first == in[1]){
                                std::string sec = it->second;
                                for(int i = 0; i < sec.length();i++){
                                    if(sec[i] ==  '\\'){
                                        std::cout<<"\n";
                                        i++;
                                    }else{
                                        std::cout<<sec[i];
                                    }
                                }
                                return true;
                            }
                        }
                    }
                    for(int i = 0; i < in[1].length();i++){
                        if(in[1][i] == '\"'){
                            return false;
                        }
                        if(in[1][i] == '\\'){
                            std::cout<<"\n";
                            i++;
                        }else if(isalnum(in[1][i]) || in[1][i] == ' '){
                            std::cout<< in[1][i];
                        }
                        if(i == in[1].length()-1){
                            return true;
                        }
                    }
                }
            }
        }
        if(in.size()>=3 && in[1] == "="){
            if(in.size() == 3){
                //Must check size of map before traversing
                if(Nmap.size() >= 1){
                    for(auto it=Nmap.begin(); it != Nmap.end();it++){
                        //Checking if index 0 exists first
                        if(it->first == in[0]){
                            //checks if all of the characters are Alphabetical or Numerical
                            for(int i = 0; i < in[2].length();i++){
                                if(isalnum(in[2][i])){
                                    continue;
                                }else {
                                    
                                    return false;
                                }
                            }
                            //If it's a number
                            if(IsNumber(in[2])){
                                it->second = stoi(in[2]);
                                return true;
                            }else{
                                //Assuming it's assigned to a var that exists
                                for(auto ir=Nmap.begin(); ir != Nmap.end();ir++){
                                    if(ir->first == in[2]){
                                        it->second = ir->second;
                                        return true;
                                    }
                                }
                                //If that doesn't work, then it doesn't exist
                                return false;
                                
                            }
                        }
                    }
                }
                if(Smap.size() >= 1){
                    //If it exists, set it equal to token, if it doesn't --Even After
                    // Going through Nmap as well, return false;
                    for(auto is=Smap.begin(); is != Smap.end();is++){
                        if(is->first == in[0]){
                            is->second = in[2];
                            return true;
                        }else {
                            continue;
                        }
                    }
                    return false;
                }
            }
        }
        //If greater than 3, it must be Nmap
        if(in.size() > 3){
                std::string expression;
                int numCount = 0;
                int OpCount = 0;
                //Now that we've counted how many members there are, let's convert any
                //Numbers already assigned
                for(size_t i = 2; i < in.size();i++){
                    if(Nmap.size() >= 1){
                        for(auto it=Nmap.begin(); it != Nmap.end(); it++){
                            if(in[i] == it->first){
                                //Converts to string for processing
                                in[i] = std::to_string(it->second);
                            }
                        }
                    }
                    if(Smap.size() >= 1){
                        for(auto it=Smap.begin(); it != Smap.end(); it++){
                            if(in[i] == it->first){
                                // Same name Variable shouldn't exist as a string
                                return false;
                            }
                        }
                    }
                    
                    //Starting as 2 since That's where the expression after = sign starts
                    
                    if(IsNumber(in[i])){
                        numCount++;
                    }
                    if(IsString(in[i])){
                        numCount++;
                    }
                    if(in[i][0] == '*' || in[i][0] == '-' || in[i][0] =='+'){
                        OpCount++;
                    }else if(in[i][0] == '\\'){
                        
                        return false;
                    }
                    expression += in[i];
                }
                    if(numCount -1 != (OpCount)){
                        return false;
                    }
                    int result = formulate(expression);
                    if(Nmap.size() > 1){
                        for(auto ip=Nmap.begin(); ip != Nmap.end(); ip++){
                            if(ip->first == in[0]){
                                ip->second = result;
                                return true;
                            }
                        }
                    }
                }
        return false;
}
    int main(int argc, char *argv[]){
        std::string current;
        if(argc > 1){
            std::string arg1(argv[1]);
            Convert(arg1);
            std::istringstream iss(input);
            int LineCounter = 0;
            while(std::getline(iss,current)){
                LineCounter++;
                std::vector<std::string> s = Parser(current);
                for(int i = 0 ; i < s.size();i++){
                }
                bool result = logic(s, LineCounter);
                if(result == false){
                    std::cout<<"Error in Line " <<  LineCounter << std::endl;
                    break;
                }
            }
        }
    }




