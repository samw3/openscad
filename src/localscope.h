#pragma once

#include "Assignment.h"
#include <unordered_map>

class LocalScope
{
public:
	LocalScope();
	~LocalScope();

	size_t numElements() const { return assignments.size() + children.size(); }
	void print(std::ostream &stream, const std::string &indent, const bool inlined = false) const;
	std::vector<class AbstractNode*> instantiateChildren(const std::shared_ptr<Context> evalctx) const;
	void addChild(class ModuleInstantiation *astnode);
	void addModule(const std::string &name, class UserModule *module);
	void addFunction(class UserFunction *function);
	void addAssignment(const class Assignment& assignment);
	void apply(const std::shared_ptr<Context> ctx) const;
	bool hasChildren() const {return !(children.empty());};

	AssignmentList assignments;
	std::vector<ModuleInstantiation*> children;

	// Modules and functions are stored twice; once for lookup and once for AST serialization
	typedef std::unordered_map<std::string, class UserFunction*> FunctionContainer;
	FunctionContainer functions;
	std::vector<std::pair<std::string, UserFunction*>> astFunctions;

	typedef std::unordered_map<std::string, class UserModule*> ModuleContainer;
	ModuleContainer	modules;
	std::vector<std::pair<std::string, UserModule*>> astModules;
};
