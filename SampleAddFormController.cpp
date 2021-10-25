#include "SampleAddFormController.h"
#include "SampleAddService.h"

void SampleAddFormController::ManageAddSampleRequest(SampleAddForm* view)
{
	SampleAddService::AddSampleRequestReceiver(view);
}