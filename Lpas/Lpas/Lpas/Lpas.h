#include <vector>
#include <string>

#include "MaquinaExecucao.h"
#include "Instruction.h"

using namespace std;

enum class LpasOperation {
	LOAD,
	RUN,
	SHOW,
	EXIT
};

class Lpas {
public:

	void run();

private:

	const map<string, LpasOperation> operations = {
		{"load", LpasOperation::LOAD},
		{"run", LpasOperation::RUN},
		{"show", LpasOperation::SHOW},
		{"exit", LpasOperation::EXIT}
	};

	MaquinaExecucao me;

	void run(Instruction instruction);

	void show(const vector<string>& args);

	void run(const vector<string>& args);

	void load(const vector<string>& args);

	Instruction extractInstruction(const string parameterizedInstruction);

	LpasOperation getOperationCode(Instruction instruction);

	void showMessage(const string& message, bool breakEndLine = true);
};
