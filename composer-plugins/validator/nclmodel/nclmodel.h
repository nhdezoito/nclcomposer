/*
 * nclmodel.h
 *
 *  Created on: 12/06/2011
 *      Author: José Rios
 */

#ifndef NCLMODEL_H_
#define NCLMODEL_H_

#include <vector>
#include <map>
#include <set>
#include <list>
#include <sstream>
#include "../definitions/definitions.h"
#include "../langstruct/langstruct.h"

namespace nclValidator {

class Model;


class ModelElement {
public:
	explicit ModelElement (virtualId parentId = "");
	~ModelElement ();


	void setElementName (string);
	void setParent (virtualId);
	void addAttribute (Attribute&);
	void addAttribute (string, string);
	void addAttribute (vector <Attribute>&);

	inline const vector<virtualId> children () const { return _children; }
	inline const vector <virtualId> references () const { return _referencesToMyself; }
	inline const virtualId & id () const { return _id; }
	inline const virtualId & parent () const { return _parentId; }
	inline const string & elementName () const { return _elementName; }
	inline const string & scope () const { return _scope; }


	inline vector <Attribute> attributes () const { return _attributes; }

	Attribute attribute (string) const;

	friend class Model;

private:
	inline void setScope (string scope) { _scope = scope; }
	inline void addReference (virtualId id) { _referencesToMyself.push_back(id); }

        bool removeReference (virtualId);
	void addChild (virtualId);
	void removeChild (virtualId);

	virtualId _id;
	virtualId _parentId;
	string _elementName;
	vector <Attribute> _attributes;
	string _scope;
	vector <virtualId> _children;
	vector <virtualId> _referencesToMyself;
};


class Model{
public:
	explicit Model ();
	~Model ();

	virtualId addChild (virtualId parentId, string elementName, vector<Attribute> attributes);
	void addChild (virtualId parent, virtualId child);
	virtualId addElement (string elementName, vector<Attribute> attributes);
	vector <ModelElement *> elementByIdentifier (string identifier);

	bool removeElement (virtualId &);
	bool editElement (virtualId &, ModelElement &);
	ModelElement * element (const virtualId &);
	set <virtualId> affectedElements ();


	inline bool hasElement (virtualId &id) { return _modelElements.count (id) > 0; }
	inline void clearMarkedElements () {_markedElements.clear(); }
	inline const set <virtualId> & markedElements () { return _markedElements; }


	void print ();

private:
	virtualId randomId ();
	void setElementId (virtualId, ModelElement &);
	void adjustScope (virtualId parent, virtualId child);
	void addChild (ModelElement *parentElement, ModelElement *childElement);

	int _seed;
	map <virtualId, ModelElement> _modelElements;
	set <virtualId> _markedElements;

	multimap <string, virtualId> _idToElement;
	multimap <string, virtualId> _elementsNotYetInserted;
};

}
#endif /* NCLMODEL_H_ */