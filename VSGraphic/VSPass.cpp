#include "VSPass.h"
#include "VSGraphicInclude.h"
using namespace VSEngine2;
IMPLEMENT_RTTI_NoCreateFun(VSPass,VSObject)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(VSPass)
IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
BEGIN_ADD_PROPERTY(VSPass,VSObject)
END_ADD_PROPERTY
VSPass::~VSPass()
{
	m_pMaterialInstance = NULL;
	m_pSpatial = NULL;
	m_pCamera = NULL;
}
VSPass::VSPass()
{
	m_pSpatial = NULL;
	m_pCamera = NULL;
	m_uiPassId = 0 ;
	m_pMaterialInstance = NULL;
}
bool VSPass::GetVShader(MaterialShaderPara& MSPara,VSShaderMap & ShaderMap,const VSUsedName &Name)
{

	VSVShader * pVertexShader = NULL;

	unsigned int uiVShaderNum = 0;


	m_pVShaderSet = ShaderMap.GetShaderSet(Name);	
	
	if (m_pVShaderSet)
	{

		uiVShaderNum = m_pVShaderSet->GetNum();
	}

	VSShaderKey::SetMaterialVShaderKey(&m_VShaderkey,MSPara,GetPassType());
	if (m_pMaterialInstance->m_pCurVShader[GetPassType()] == NULL)
	{
		if (m_pVShaderSet)
		{
			unsigned int uiIndex = m_pVShaderSet->Find(m_VShaderkey);

			if (uiIndex != m_pVShaderSet->GetNum())
			{
				VSShader * pTemp = (*m_pVShaderSet)[uiIndex].Value;
				pVertexShader = (VSVShader *)(pTemp);
			}

		}
		if (pVertexShader == NULL)
		{
			pVertexShader = VSResourceManager::CreateVShader(MSPara,GetPassType(),uiVShaderNum);
			if (!pVertexShader)
			{
				return 0;
			}
			if (m_pVShaderSet)
			{
				m_pVShaderSet->AddElement(m_VShaderkey,pVertexShader);
			}
		}
		m_pMaterialInstance->m_pCurVShader[GetPassType()] = pVertexShader;
	}
	else
	{
		if (m_pMaterialInstance->m_pCurVShader[GetPassType()]->m_ShaderKey == m_VShaderkey)
		{

		}
		else
		{

			if (m_pVShaderSet)
			{
				unsigned int uiIndex = m_pVShaderSet->Find(m_VShaderkey);

				if (uiIndex != m_pVShaderSet->GetNum())
				{
					VSShader * pTemp = (*m_pVShaderSet)[uiIndex].Value;
					pVertexShader = (VSVShader *)(pTemp);
				}
			}
			if (pVertexShader == NULL)
			{
				pVertexShader = VSResourceManager::CreateVShader(MSPara,GetPassType(),uiVShaderNum);
				if (!pVertexShader)
				{
					return 0;
				}
				if (m_pVShaderSet)
				{
					m_pVShaderSet->AddElement(m_VShaderkey,pVertexShader);
				}
			}
			m_pMaterialInstance->m_pCurVShader[GetPassType()] = pVertexShader;
		}
	}

	if (!m_pVShaderSet)
	{
		ShaderMap.SetShader(Name,m_VShaderkey,pVertexShader);
		m_pVShaderSet = ShaderMap.GetShaderSet(Name);
	}
	return 1;
}
bool VSPass::GetPShader(MaterialShaderPara& MSPara,VSShaderMap & ShaderMap,const VSUsedName &Name)
{

	unsigned int uiPShaderNum = 0;
	VSPShader * pPixelShader = NULL;


	m_pPShaderSet = ShaderMap.GetShaderSet(Name);
	
	if (m_pPShaderSet)
	{
		uiPShaderNum = m_pPShaderSet->GetNum();
	}

	VSShaderKey::SetMaterialPShaderKey(&m_PShaderkey,MSPara,GetPassType());

	if (m_pMaterialInstance->m_pCurPShader[GetPassType()] == NULL)
	{
		if (m_pPShaderSet)
		{
			unsigned int uiIndex = m_pPShaderSet->Find(m_PShaderkey);

			if (uiIndex != m_pPShaderSet->GetNum())
			{
				VSShader * pTemp = (*m_pPShaderSet)[uiIndex].Value;
				pPixelShader = (VSPShader *)(pTemp);
			}
		}
		if (pPixelShader == NULL)
		{
			pPixelShader = VSResourceManager::CreatePShader(MSPara,GetPassType(),uiPShaderNum);
			if (!pPixelShader)
			{
				return 0;
			}
			if (m_pPShaderSet)
			{
				m_pPShaderSet->AddElement(m_PShaderkey,pPixelShader);
			}
		}
		m_pMaterialInstance->m_pCurPShader[GetPassType()] = pPixelShader;
	}
	else
	{
		if (m_pMaterialInstance->m_pCurPShader[GetPassType()]->m_ShaderKey == m_PShaderkey)
		{

		}
		else
		{
			if (m_pPShaderSet)
			{
				unsigned int uiIndex = m_pPShaderSet->Find(m_PShaderkey);

				if (uiIndex != m_pPShaderSet->GetNum())
				{
					VSShader * pTemp = (*m_pPShaderSet)[uiIndex].Value;
					pPixelShader = (VSPShader *)(pTemp);
				}
			}
			if (pPixelShader == NULL)
			{
				pPixelShader = VSResourceManager::CreatePShader(MSPara,GetPassType(),uiPShaderNum);
				if (!pPixelShader)
				{
					return 0;
				}
				if (m_pPShaderSet)
				{
					m_pPShaderSet->AddElement(m_PShaderkey,pPixelShader);
				}
			}
			m_pMaterialInstance->m_pCurPShader[GetPassType()] = pPixelShader;
		}
	}

	if (!m_pPShaderSet)
	{
		ShaderMap.SetShader(Name,m_PShaderkey,pPixelShader);
		m_pPShaderSet = ShaderMap.GetShaderSet(Name);
	}
	return 1;
}
