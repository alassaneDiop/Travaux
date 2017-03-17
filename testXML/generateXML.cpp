#include "stdio.h"
#include "tinyxml2/tinyxml2.h"
#include <iostream>

using namespace std;
using namespace tinyxml2;

/*#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif
*/
int main () {

	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("SavedData.xml");
	XMLNode * pRoot = xmlDoc.FirstChild();

	if (pRoot != NULL) {
		XMLElement * pElement = pRoot->FirstChildElement("IntValue");

		if (pElement != NULL) {
			int iOutInt;
			eResult = pElement->QueryIntText(&iOutInt);
			cout << eResult << iOutInt << endl;

			pElement = pRoot->FirstChildElement("List");

			if (pElement == nullptr) {
				XMLElement * pListElement = pElement->FirstChildElement("Item");
				vector<int> vecList;
				// a suivre
			} else {
				cout << XML_ERROR_PARSING_ELEMENT;
			}
			//cout << XMLCheckResult(eResult);

			//	cout << XMLCheckResult(eResult);
		} else
			cout << XML_ERROR_PARSING_ELEMENT;

	} else {
		cout << XML_ERROR_FILE_READ_ERROR;
	}

	
	return 0;
}
