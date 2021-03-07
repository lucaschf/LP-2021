#include <vector>
#include <string>

#include "MaquinaExecucao.h"
#include "Operation.h"

using namespace std;

// represents all available operations of lpass
enum class LpasOperation {
	LOAD,
	RUN,
	SHOW,
	EXIT
};

class Lpas {
public:

	// start execution
	void run();

private:

	// mapping of all available operations
	const map<string, LpasOperation> operationsMapping = {
		{"load", LpasOperation::LOAD},
		{"run", LpasOperation::RUN},
		{"show", LpasOperation::SHOW},
		{"exit", LpasOperation::EXIT}
	};

	MaquinaExecucao me;

	// Performs an operation based on its name and arguments
	void run(Operation instruction);

	// shows programs in memory
	void show(const vector<string>& args);

	// run a specific program
	void run(const vector<string>& args);

	/*
	* Load all lpas programs into memory based on location passed through args
	*/
	void load(const vector<string>& args);

	/*
	* Extract a parameterized operation from a string
	*/
	Operation extractOperation(const string parameterizedOperation);

	/*Converts the LPAS operation to its equivalent machine code based on the operationsMapping mapping.
	Returns the machine code for the LPAS operation.*/
	LpasOperation getOperationCode(Operation instruction);

	// shows a message in console
	void showMessage(const string& message, bool breakEndLine = true);
};
