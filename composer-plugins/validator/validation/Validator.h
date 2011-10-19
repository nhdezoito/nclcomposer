/*
 * Validator.h
 *
 *  Created on: 29 Aug 2011
 *      Author: rios
 */

#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include <list>

#include "../nclmodel/nclmodel.h"
#include "../langstruct/langstruct.h"
#include "../message/message.h"

namespace nclValidator {

class Validator {
	public:
                static vector<string> validate (Model &);
};

}

#endif /* VALIDATOR_H_ */
