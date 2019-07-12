#pragma once

class C_Model;

struct S_ModelComponent
{
	S_ModelComponent();
	S_ModelComponent(C_Model * model);

	C_Model * m_Model;
};