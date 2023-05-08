#include <stdio.h>
#include <json-c/json.h>

int main()
{
	json_object* root = json_object_new_object();
	json_object_object_add(root, "name", json_object_new_string("John Doe"));
	json_object_object_add(root, "age", json_object_new_int(30));

	const char* jsonString = json_object_to_json_string(root);
	printf("%s\n",jsonString);

	json_object_put(root);

return 0;
}
