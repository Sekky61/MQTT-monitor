/*! \file tree_node.hpp
    \brief Genericky strom
    
    Trida TreeNode<T> implementujici strom.
*/

#ifndef TR_NDE
#define TR_NDE

#include <vector>
#include <string>
#include <sstream>

/**
 * \brief Generický strom
 * \details 
 */
template<typename T>
class TreeNode
{
	/**
	 * \brief rozdělí název tématu podle znaku '/'
	 * \param topic_name název tématu
	 * \return Vektor řetězců 
	 */
	std::vector<std::string> cut_topic_path(std::string topic_name){
		std::istringstream input;
    	input.str(topic_name);

		std::vector<std::string> cut;
    	for (std::string line; std::getline(input, line, '/'); ) {
    		cut.emplace_back(line);
		}
		return cut;
	}

public:

	std::string Topic;
	std::string fullTopic;

	bool is_start_of_wildcard;

	unsigned long limit;
	std::deque<T> Msgs;

    std::vector<std::unique_ptr<TreeNode<T> > > Children;
	TreeNode<T> *Parent;

    TreeNode(): 
		is_start_of_wildcard(false), 
		Parent(nullptr) {}

	/**
	 * \brief Konstruktor.
	 */
    TreeNode(TreeNode<T> *parent_ptr, std::string topic_name, std::string full_topic) :
		Topic(topic_name),
		fullTopic(full_topic),
		is_start_of_wildcard(false),
		limit(0),
		Msgs(),
		Children(),
		Parent(parent_ptr) {} // const T& value // todo move && ?

	/**
	 * \brief vrací nejnovější zprávu
	 */
	T *get_latest_msg(){
		if (Msgs.empty()){
			return nullptr;
		}
		return &Msgs.back();
	}

	/**
	 * \brief Rekurzivně nastaví nový limit historie
	 */
	void set_limit_recursive(int new_limit){
		set_limit(new_limit);

		for(auto &child : Children){
			child->set_limit_recursive(limit);
		}
	}

	/**
	 * \brief nastaví nový limit historie
	 */
	void set_limit(int new_limit){
		limit = new_limit;

		while(limit != 0 && limit < Msgs.size()){
			std::cerr << "set_limit: Size is " << Msgs.size() << " limit is " << limit << " and I must pop\n";
			Msgs.pop_front();
		}
	}

	void set_topic(std::string topic){
		// todo checks
		Topic = topic;
	}

	/**
	 * \brief přidá zprávu do historie
	 * \details podle omezení na velikost historie může odebrat zprávu
	 * \param message zpráva přidávaná do historie
	 */
	void add_message(T message){
		if(limit != 0 && limit <= Msgs.size()){
			Msgs.pop_front();
			Msgs.push_back(message);
		} else {
			Msgs.push_back(message);
		}
	}

	/**
	 * \brief Vrací odkaz na potomka podle jeho tématu
	 * \param name název podtématu
	 */
	TreeNode<T> *get_child(std::string name){
		auto x = std::find_if(
			Children.begin(), 
			Children.end(),
			[&] (auto &s) { return s->Topic == name; });
		if (x != Children.end()){
			// child exists
			return (*x).get();
		}
		return nullptr;
	}

        TreeNode<T> *get_child_by_index(size_t index){
		if (index >= 0 && index < Children.size()){
			// child exists
			return Children[index].get();
		}
		return nullptr;
	}

        size_t number_of_children(){
		return Children.size();
	}

	/**
	 * \brief získá vlastní index (u rodiče)
	 */
	int get_own_index(){
		if(!Parent){
			return -1;
		}
                auto it = find_if(
			Parent->Children.begin(), 
			Parent->Children.end(), 
			[&] (auto &s) { return s.get() == this; });
		if (it != Parent->Children.end())
    	{
			// found
        	return it - Parent->Children.begin();
    	}
    	else {
        	return -1;
    	}
	}

	/**
	 * \brief Vrací uzel podle \ref name.
	 * \details Najde potomka, nebo takový uzel vytvoří
	 * \param name Název podtématu potomka
	 */
	TreeNode<T> *get_create_child(std::string name){
		auto *child_node = get_child(name);
		if (child_node == nullptr){
			// child does not exists
			std::string new_full = (fullTopic == "" ? "" : fullTopic + "/" ) + name;
			std::unique_ptr<TreeNode<T> > new_node = std::make_unique<TreeNode<T> >(this, name, new_full);
			Children.emplace_back(std::move(new_node));
			return Children.back().get();
		}
		return child_node;
	}

	TreeNode<T> *grow_tree(std::string topic_name){

		std::vector<std::string> cut = cut_topic_path(topic_name);

		TreeNode<T> *node = this;
		
		for(std::string name : cut){
			if(name == "#"){
				node->is_start_of_wildcard = true;
				break;
			}
			node = node->get_create_child(name);
		}

		return node;
	}

	void delete_children(){
		Children.clear();
		Children.shrink_to_fit();
	}
};

#endif
