
class variable{
	public:
		variable(){

		}

		virtual string print(){return (string)"object";};
		virtual string get_type			(				 );
		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other);
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 );
		virtual variable * _call		(variable * other);
};

class None_var: public variable{
	public:
		None_var(){

		}

		virtual string print(){return (string)"None";};
		virtual string get_type	(){return (string)"None_var";};
		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other);
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 );
		virtual variable * _call		(variable * other);
};

ostream & operator<<(ostream & os, stack<variable *> my_stack) //function header
{
	cout << "[";
    while(!my_stack.empty()) //body
    {	
        os << my_stack.top()->print()<< " ";
        my_stack.pop();
    }
    cout << "]"<<endl;
    return os; // end of function
}

class Exception: public variable{
	public:
		string message = "";
		string type = "Exception";
		
		void raise(string message = ""){
			if(message==""){
				message = this->message;
			}

			cout<<this->type<<endl;
			cout<<message<<endl;
			exit(0);
		};


		Exception(string type, string message){
			this->type = type;
			this->message = message;
			this->raise();
		}
		Exception(string message){
			this->message = message;
			this->raise();
		}
		Exception(){
			this->raise();
		}	
};


class SyntaxError: public Exception{
	public:
		SyntaxError(string message) 
		: Exception("SyntaxError", message){}
};

class TypeError: public Exception{
	public:
		TypeError(string message) 
		: Exception("TypeError", message){}
};

class ValueError: public Exception{
	public:
		ValueError(string message) 
		: Exception("ValueError", message){}
};

class float_var: public variable{
	public:
		float val;

		virtual string print(){return to_string(val);}

		float_var(float val = 0){
			this->val = val;
		}

		virtual string get_type(){
			return (string)"float_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 ){
			return new float_var(this->val);
		};
		virtual variable * _call		(variable * other);
};


class int_var: public variable{
	public:
		int val;

		int_var(int val = 0){
			this->val = val;
		}

		virtual string print(){return to_string(val);}

		virtual string get_type(){
			return (string)"int_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 ){
			return new int_var(this->val);
		};
		virtual variable * _call		(variable * other);
};

class list_var: public variable{
	public:
		vector<variable *> vals;

		list_var(vector<variable *> vals){
			this->vals = vals;
		}

		list_var(){
			this->vals = {};
		}

		void from_vector(vector<variable *> items){
			this->vals = items;
		}

		virtual string print(){
			string ret = "[";
			for (int i = 0; i < this->vals.size(); ++i)
			{
				ret += this->vals.at(i)->print();
				ret += ", ";
			}
			ret  = ret.substr(0, ret.size()-1);
			ret += "]";
			return ret;
		}

		virtual string get_type(){
			return (string)"list_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 ){
			return new list_var(this->vals);
		};
		virtual variable * _call		(variable * other);
};


class tuple_var: public variable{
	public:
		vector<variable *> vals;

		tuple_var(vector<variable *> vals){
			this->vals = vals;
		}

		tuple_var(){
			this->vals = {};
		}

		void from_vector(vector<variable *> items){
			this->vals = items;
		}

		virtual string print(){
			string ret = "(";
			for (int i = 0; i < this->vals.size(); ++i)
			{
				ret += this->vals.at(i)->print();
				ret += ", ";
			}
			ret = ret.substr(0, ret.size()-2);
			ret += ")";
			return ret;
		}

		virtual string get_type(){
			return (string)"tuple_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 ){
			return new tuple_var(this->vals);
		};
		virtual variable * _call		(variable * other);
};


class string_var: public variable{
	public:
		string val;

		string_var(string val){
			this->val = val;
		}

		string_var(){
			this->val = "";
		}

		void from_string(string item){
			this->val = item;
		}

		virtual string print(){
			string ret = "";
			ret += this->val;
			ret += "";
			return ret;
		}

		virtual string get_type(){
			return (string)"string_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 ){
			return new string_var(this->val);
		};
		virtual variable * _call		(variable * other);
};


class cpp_function_var: public variable{
	public:
		variable * (* func)(tuple_var *);
		cpp_function_var(variable * (*func)(tuple_var *)){
			this->func = func;
		}

		virtual string print(){
			return"cpp_function object";
		}

		virtual string get_type(){
			return (string)"cpp_function_var";
		}

		virtual variable * _add			(variable * other);
		virtual variable * _sub			(variable * other); 
		virtual variable * _mul			(variable * other);
		virtual variable * _div			(variable * other);
		virtual variable * _unary_neg	(				 );
		virtual variable * _pow			(variable * other);
		virtual variable * copy		 	(				 ){
			return new cpp_function_var(this->func);
		};
		virtual variable * _call		(variable * other);
};

string variable::get_type			(				 ){TypeError(this->print() + string(" does not support the get_type operation")); return NULL;};
variable * variable::_add			(variable * other){TypeError(this->print() + string(" does not support the add operation")); return NULL;};
variable * variable::_sub			(variable * other){TypeError(this->print() + string(" does not support the sub operation")); return NULL;};
variable * variable::_mul			(variable * other){TypeError(this->print() + string(" does not support the mul operation")); return NULL;};
variable * variable::_div			(variable * other){TypeError(this->print() + string(" does not support the div operation")); return NULL;};
variable * variable::_unary_neg		(				 ){TypeError(this->print() + string(" does not support the unary_neg operation")); return NULL;};
variable * variable::_pow			(variable * other){TypeError(this->print() + string(" does not support the pow operation")); return NULL;};
variable * variable::copy			(				 ){TypeError(this->print() + string(" does not support the pow operation")); return NULL;};
variable * variable::_call			(variable * other){TypeError(this->print() + string(" does not support the pow operation")); return NULL;};

variable * None_var::_add			(variable * other){TypeError(this->print() + string(" does not support the add operation")); return NULL;};
variable * None_var::_sub			(variable * other){TypeError(this->print() + string(" does not support the sub operation")); return NULL;};
variable * None_var::_mul			(variable * other){TypeError(this->print() + string(" does not support the mul operation")); return NULL;};
variable * None_var::_div			(variable * other){TypeError(this->print() + string(" does not support the div operation")); return NULL;};
variable * None_var::_unary_neg		(				 ){TypeError(this->print() + string(" does not support the unary_neg operation")); return NULL;};
variable * None_var::_pow			(variable * other){TypeError(this->print() + string(" does not support the pow operation")); return NULL;};
variable * None_var::copy			(				 ){TypeError(this->print() + string(" does not support the pow operation")); return NULL;};
variable * None_var::_call			(variable * other){TypeError(this->print() + string(" does not support the pow operation")); return NULL;};	

variable * cpp_function_var::_add			(variable * other){TypeError(this->print() + string(" does not support the add operation")); return NULL;};
variable * cpp_function_var::_sub			(variable * other){TypeError(this->print() + string(" does not support the sub operation")); return NULL;};
variable * cpp_function_var::_mul			(variable * other){TypeError(this->print() + string(" does not support the mul operation")); return NULL;};
variable * cpp_function_var::_div			(variable * other){TypeError(this->print() + string(" does not support the div operation")); return NULL;};
variable * cpp_function_var::_unary_neg		(				 ){TypeError(this->print() + string(" does not support the unary_neg operation")); return NULL;};
variable * cpp_function_var::_pow			(variable * other){TypeError(this->print() + string(" does not support the pow operation")); return NULL;};
variable * cpp_function_var::_call			(variable * other){
	if(other->get_type() == "tuple_var"){
		variable * a = this->func(dynamic_cast<tuple_var *>(other));
	}else{
		SyntaxError("INVALID FUNCTION CALL");
	}
};


variable * list_var::_add(variable * other){
	if(other->get_type() == "list_var"){
		list_var *other_t = dynamic_cast<list_var *>(other);
		this->vals.reserve(this->vals.size() + other_t->vals.size());
		this->vals.insert(this->vals.end(), other_t->vals.begin(), other_t->vals.end());
		return this;
	}
	TypeError(this->print() + string("does not support the add operation on objects other than list_var"));
	return NULL;
}

variable * list_var::_sub(variable * other){
	TypeError(this->print() + string("does not support the sub operation"));
	return NULL;
}

variable * list_var::_mul(variable * other){
	if(other->get_type() == "int_var"){
		//
	}
	TypeError(this->print() + string("does not support the mul operation"));
	return NULL;
}

variable * list_var::_div(variable * other){
	TypeError(this->print() + string("does not support the div operation"));
	return NULL;
}

variable * list_var::_unary_neg(){
	TypeError(this->print() + string("does not support the unary_neg operation"));
	return NULL;
}

variable * list_var::_pow(variable * other){
	TypeError(this->print() + string("does not support the pow operation"));
	return NULL;
}
variable * list_var::_call(variable * other){
	TypeError(this->print() + string("does not support the call operation"));
	return NULL;
}


variable * tuple_var::_add(variable * other){
	TypeError(this->print() + string("does not support the add operation on objects other than tuple_var"));
	return NULL;
}

variable * tuple_var::_sub(variable * other){
	TypeError(this->print() + string("does not support the sub operation"));
	return NULL;
}

variable * tuple_var::_mul(variable * other){
	TypeError(this->print() + string("does not support the mul operation"));
	return NULL;
}

variable * tuple_var::_div(variable * other){
	TypeError(this->print() + string("does not support the div operation"));
	return NULL;
}

variable * tuple_var::_unary_neg(){
	TypeError(this->print() + string("does not support the unary_neg operation"));
	return NULL;
}

variable * tuple_var::_pow(variable * other){
	TypeError(this->print() + string("does not support the pow operation"));
	return NULL;
}
variable * tuple_var::_call(variable * other){
	TypeError(this->print() + string("does not support the call operation"));
	return NULL;
}

variable * string_var::_add(variable * other){
	if(other->get_type() == "string_var"){
		string_var *other_t = dynamic_cast<string_var *>(other);
		return new string_var(this->val + other_t->val);
	}
	TypeError(this->print() + string("does not support the add operation on objects other than list_var"));
	return NULL;
}

variable * string_var::_sub(variable * other){
	TypeError(this->print() + string("does not support the sub operation"));
	return NULL;
}

variable * string_var::_mul(variable * other){
	if(other->get_type() == "int_var"){
		//
	}
	TypeError(this->print() + string("does not support the mul operation"));
	return NULL;
}

variable * string_var::_div(variable * other){
	TypeError(this->print() + string("does not support the div operation"));
	return NULL;
}

variable * string_var::_unary_neg(){
	TypeError(this->print() + string("does not support the unary_neg operation"));
	return NULL;
}

variable * string_var::_pow(variable * other){
	TypeError(this->print() + string("does not support the pow operation"));
	return NULL;
}
variable * string_var::_call(variable * other){
	TypeError(this->print() + string("does not support the call operation"));
	return NULL;
}

variable * float_var::_add(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(this->val + (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val + dynamic_cast<float_var *>(other)->val);
	}
	return NULL;
}
variable * float_var::_sub(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(this->val - (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val - dynamic_cast<float_var *>(other)->val);
	}
	return NULL;
}
variable * float_var::_mul(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(this->val * (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val * dynamic_cast<float_var *>(other)->val);
	}

	return NULL;
}
variable * float_var::_div(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var((float)this->val / (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var(this->val / dynamic_cast<float_var *>(other)->val);
	}
	return NULL;
}	
variable * float_var::_unary_neg(){
	return new float_var(-this->val);
}

variable * float_var::_pow(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var(pow(this->val,(float)dynamic_cast<int_var *>(other)->val));
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)pow(this->val, dynamic_cast<float_var *>(other)->val));
	}
	return NULL;
}
variable * float_var::_call(variable * other){
	TypeError(this->print() + string("does not support the call operation"));
	return NULL;
}


variable * int_var::_add(variable * other){
	if(other->get_type() =="int_var"){
		return new int_var(this->val + dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val + dynamic_cast<float_var *>(other)->val);
	}
	return NULL;
}
variable * int_var::_sub(variable * other){
	if(other->get_type() =="int_var"){
		return new int_var(this->val - dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val - dynamic_cast<float_var *>(other)->val);
	}
	return NULL;
}
variable * int_var::_mul(variable * other){
	if(other->get_type() =="int_var"){
		return new int_var(this->val * dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val * dynamic_cast<float_var *>(other)->val);
	}
	return NULL;	
}
variable * int_var::_div(variable * other){
	if(other->get_type() =="int_var"){
		return new float_var((float)this->val / (float)dynamic_cast<int_var *>(other)->val);
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)this->val / dynamic_cast<float_var *>(other)->val);
	}
	return NULL;
}

variable * int_var::_unary_neg(){
	return new int_var(-this->val);
}

variable * int_var::_pow(variable * other){			
	if(other->get_type() =="int_var"){
		return new int_var(pow(this->val,dynamic_cast<int_var *>(other)->val));
	}
	if(other->get_type() =="float_var"){
		return new float_var((float)pow(this->val, dynamic_cast<float_var *>(other)->val));
	}
	return NULL;
}

variable * int_var::_call(variable * other){
	TypeError(this->print() + string("does not support the call operation"));
	return NULL;
}