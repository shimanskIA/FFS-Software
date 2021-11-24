#pragma once

#include "ui_ParameterAddForm.h"
#include "ParameterAddForm.h"
#include "ErrorForm.h"

#include <QString>

static class ParameterAddFormController
{
public:
	static void ManageAddParameterRequest(ParameterAddForm* view);
	static void ManageAddButtonActivity(ParameterAddForm* view);
};