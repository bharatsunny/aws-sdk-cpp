﻿/*
* Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#include <aws/s3control/model/OperationName.h>
#include <aws/core/utils/HashingUtils.h>
#include <aws/core/Globals.h>
#include <aws/core/utils/EnumParseOverflowContainer.h>

using namespace Aws::Utils;


namespace Aws
{
  namespace S3Control
  {
    namespace Model
    {
      namespace OperationNameMapper
      {

        static const int LambdaInvoke_HASH = HashingUtils::HashString("LambdaInvoke");
        static const int S3PutObjectCopy_HASH = HashingUtils::HashString("S3PutObjectCopy");
        static const int S3PutObjectAcl_HASH = HashingUtils::HashString("S3PutObjectAcl");
        static const int S3PutObjectTagging_HASH = HashingUtils::HashString("S3PutObjectTagging");
        static const int S3InitiateRestoreObject_HASH = HashingUtils::HashString("S3InitiateRestoreObject");
        static const int S3PutObjectLegalHold_HASH = HashingUtils::HashString("S3PutObjectLegalHold");
        static const int S3PutObjectRetention_HASH = HashingUtils::HashString("S3PutObjectRetention");


        OperationName GetOperationNameForName(const Aws::String& name)
        {
          int hashCode = HashingUtils::HashString(name.c_str());
          if (hashCode == LambdaInvoke_HASH)
          {
            return OperationName::LambdaInvoke;
          }
          else if (hashCode == S3PutObjectCopy_HASH)
          {
            return OperationName::S3PutObjectCopy;
          }
          else if (hashCode == S3PutObjectAcl_HASH)
          {
            return OperationName::S3PutObjectAcl;
          }
          else if (hashCode == S3PutObjectTagging_HASH)
          {
            return OperationName::S3PutObjectTagging;
          }
          else if (hashCode == S3InitiateRestoreObject_HASH)
          {
            return OperationName::S3InitiateRestoreObject;
          }
          else if (hashCode == S3PutObjectLegalHold_HASH)
          {
            return OperationName::S3PutObjectLegalHold;
          }
          else if (hashCode == S3PutObjectRetention_HASH)
          {
            return OperationName::S3PutObjectRetention;
          }
          EnumParseOverflowContainer* overflowContainer = Aws::GetEnumOverflowContainer();
          if(overflowContainer)
          {
            overflowContainer->StoreOverflow(hashCode, name);
            return static_cast<OperationName>(hashCode);
          }

          return OperationName::NOT_SET;
        }

        Aws::String GetNameForOperationName(OperationName enumValue)
        {
          switch(enumValue)
          {
          case OperationName::LambdaInvoke:
            return "LambdaInvoke";
          case OperationName::S3PutObjectCopy:
            return "S3PutObjectCopy";
          case OperationName::S3PutObjectAcl:
            return "S3PutObjectAcl";
          case OperationName::S3PutObjectTagging:
            return "S3PutObjectTagging";
          case OperationName::S3InitiateRestoreObject:
            return "S3InitiateRestoreObject";
          case OperationName::S3PutObjectLegalHold:
            return "S3PutObjectLegalHold";
          case OperationName::S3PutObjectRetention:
            return "S3PutObjectRetention";
          default:
            EnumParseOverflowContainer* overflowContainer = Aws::GetEnumOverflowContainer();
            if(overflowContainer)
            {
              return overflowContainer->RetrieveOverflow(static_cast<int>(enumValue));
            }

            return {};
          }
        }

      } // namespace OperationNameMapper
    } // namespace Model
  } // namespace S3Control
} // namespace Aws
