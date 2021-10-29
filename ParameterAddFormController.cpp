#include "ParameterAddFormController.h"
#include "ParameterAddService.h"

void ParameterAddFormController::ManageAddParameterRequest(ParameterAddForm* view)
{
	ParameterAddService::AddParameterRequestReceiver(view);
}