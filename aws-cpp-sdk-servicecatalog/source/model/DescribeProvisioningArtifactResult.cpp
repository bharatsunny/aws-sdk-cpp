﻿/*
* Copyright 2010-2016 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License").
* You may not use this file except in compliance with the License.
* A copy of the License is located at
*
*  http://aws.amazon.com/apache2.0
*
* or in the "license" file accompanying this file. This file is distributed
* on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied. See the License for the specific language governing
* permissions and limitations under the License.
*/
#include <aws/servicecatalog/model/DescribeProvisioningArtifactResult.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/AmazonWebServiceResult.h>
#include <aws/core/utils/UnreferencedParam.h>

#include <utility>

using namespace Aws::ServiceCatalog::Model;
using namespace Aws::Utils::Json;
using namespace Aws::Utils;
using namespace Aws;

DescribeProvisioningArtifactResult::DescribeProvisioningArtifactResult() : 
    m_status(Status::NOT_SET)
{
}

DescribeProvisioningArtifactResult::DescribeProvisioningArtifactResult(const AmazonWebServiceResult<JsonValue>& result) : 
    m_status(Status::NOT_SET)
{
  *this = result;
}

DescribeProvisioningArtifactResult& DescribeProvisioningArtifactResult::operator =(const AmazonWebServiceResult<JsonValue>& result)
{
  const JsonValue& jsonValue = result.GetPayload();
  if(jsonValue.ValueExists("ProvisioningArtifactDetail"))
  {
    m_provisioningArtifactDetail = jsonValue.GetObject("ProvisioningArtifactDetail");

  }

  if(jsonValue.ValueExists("Info"))
  {
    Aws::Map<Aws::String, JsonValue> infoJsonMap = jsonValue.GetObject("Info").GetAllObjects();
    for(auto& infoItem : infoJsonMap)
    {
      m_info[infoItem.first] = infoItem.second.AsString();
    }
  }

  if(jsonValue.ValueExists("Status"))
  {
    m_status = StatusMapper::GetStatusForName(jsonValue.GetString("Status"));

  }



  return *this;
}