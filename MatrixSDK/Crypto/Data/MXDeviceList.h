/*
 Copyright 2017 Vector Creations Ltd

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <Foundation/Foundation.h>

#import "MXSDKOptions.h"

#ifdef MX_CRYPTO

#import "MXDeviceInfo.h"
#import "MXCryptoConstants.h"

#import "MXRestClient.h"

@class MXCrypto;

/**
 `MXDeviceList` manages the list of other users' devices.
 */
@interface MXDeviceList : NSObject

/**
 The last sync token.
 */
@property (nonatomic) NSString *lastKnownSyncToken;

/**
 Constructor.
 
 @param crypto the MXCrypto instance.
 @return a new MXDeviceList instance.
 */
- (id)initWithCrypto:(MXCrypto*)crypto;

/**
 Download the device keys for a list of users and stores the keys in the MXStore.

 @param userIds The users to fetch.
 @param forceDownload Always download the keys even if cached.

 @param success A block object called when the operation succeeds.
 @param failure A block object called when the operation fails.

 @return a MXHTTPOperation instance. May be nil if the data is already in the store.
 */
- (MXHTTPOperation*)downloadKeys:(NSArray<NSString*>*)userIds forceDownload:(BOOL)forceDownload
                         success:(void (^)(MXUsersDevicesMap<MXDeviceInfo*> *usersDevicesInfoMap))success
                         failure:(void (^)(NSError *error))failure;

/**
 Get the stored device keys for a user.

 @param userId the user to list keys for.
 @return the list of devices.
 */
- (NSArray<MXDeviceInfo*>*)storedDevicesForUser:(NSString*)userId;

/**
 Find a device by curve25519 identity key

 @param userId the owner of the device.
 @param algorithm the encryption algorithm.
 @param senderKey the curve25519 key to match.
 @return the device info.
 */
- (MXDeviceInfo*)deviceWithIdentityKey:(NSString*)senderKey forUser:(NSString*)userId andAlgorithm:(NSString*)algorithm;

/**
 Mark the cached device list for the given user outdated.

 This doesn't set off an update, so that several users can be batched
 together. Call refreshOutdatedDeviceLists for that.

 @param userId.
 */
- (void)invalidateUserDeviceList:(NSString*)userId;

/**
 If there is not already a device list query in progress, and we have
 users who have outdated device lists, start a query now.
 */
- (void)refreshOutdatedDeviceLists;

@end

#endif
