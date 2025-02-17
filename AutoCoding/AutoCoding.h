//
//  AutoCoding.h
//
//  Version 2.2.3
//
//  Created by Nick Lockwood on 19/11/2011.
//  Copyright (c) 2011 Charcoal Design
//
//  Distributed under the permissive zlib License
//  Get the latest version from here:
//
//  https://github.com/nicklockwood/AutoCoding
//
//  This software is provided 'as-is', without any express or implied warranty.
//  In no event will the authors be held liable for any damages arising from the
//  use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software in a
//  product, an acknowledgment in the product documentation would be appreciated
//  but is not required.
//
//  2. Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//
//  3. This notice may not be removed or altered from any source distribution.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSObject (AutoCoding) <NSSecureCoding>

/**
 * Returns a dictionary containing the names and classes of all the properties of
 * the class that will be automatically saved, loaded and copied when the object
 * is archived using `NSKeyedArchiver/Unarchiver`. The values of the dictionary
 * represent the class used to encode each property (e.g. `NSString` for strings,
 * `NSNumber` for numeric values or booleans, `NSValue` for structs, etc).
 *
 * This dictionary is automatically generated by scanning the properties defined
 * in the class definition at runtime. Read-only and private properties will also
 * be coded as long as they have KVC-compliant ivar names (i.e. the ivar matches
 * the property name, or is the same but with a _ prefix). Any properties that
 * are not backed by an ivar, or whose ivar name does not match the property name
 * will not be encoded (this is a design feature, not a limitation - it makes it
 * easier to exclude properties from encoding)
 *
 * It is not normally necessary to override this method unless you wish to add
 * ivars for coding that do not have matching property definitions, or if you
 * wish to code virtual properties (properties or setter/getter method pairs that
 * are not backed by an ivar). If you wish to exclude certain properties from the
 * serialisation process, you can deliberately give them an non KVC-compliant
 * ivar name (see above).
 *
 * Note that this method only returns the properties defined on a particular
 * class and not any properties that are inherited from its superclasses. You
 * *do not* need to call `[super codableProperties]` if you override this method.
 */
+ (NSDictionary<NSString *, Class> *)codableProperties;

/**
 * Populates the object's properties using the provided `NSCoder` object, based
 * on the `codableProperties` dictionary. This is called internally by the
 * `initWithCoder:` method, but may be useful if you wish to initialise an object
 * from a coded archive after it has already been created. You could even
 * initialise the object by merging the results of several different archives by
 * calling `setWithCoder:` more than once.
 */
 - (void)setWithCoder:(NSCoder *)aDecoder;

/**
 * Returns all the codable properties of the object, including those that are
 * inherited from superclasses. You should not override this method - if you
 * want to add additional properties, override the `+codableProperties` class
 * method instead.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, Class> *codableProperties;
 
/**
 * Returns a dictionary of the values of all the codable properties of the
 * object. It is equivalent to calling `dictionaryWithValuesForKeys:` with the
 * result of `object.codableProperties.allKeys` as the parameter.
 */
@property (nonatomic, readonly) NSDictionary<NSString *, id> *dictionaryRepresentation;

/**
 * Attempts to load the file using the following sequence: 1) If the file is an
 * NSCoded archive, load the root object and return it; 2) If the file is an
 * ordinary Plist, load and return the root object; 3) Return the raw data as an
 * `NSData` object. If the de-serialised object is not a subclass of the class
 * being used to load it, an exception will be thrown (to avoid this, call the
 * method on `NSObject` instead of a specific subclass).
 */
+ (nullable instancetype)objectWithContentsOfFile:(NSString *)path;

/**
 * Attempts to write the file to disk. This method is overridden by the
 * equivalent methods for `NSData`, `NSDictionary` and `NSArray`, which save the
 * file as a human-readable XML Plist rather than a binary NSCoded Plist archive,
 * but the `objectWithContentsOfFile:` method will correctly de-serialise these
 * again anyway. For any other object it will serialise the object using the
 * `NSCoding` protocol and write out the file as a NSCoded binary Plist archive.
 * Returns `YES` on success and `NO` on failure.
 */
- (BOOL)writeToFile:(NSString *)filePath atomically:(BOOL)useAuxiliaryFile;

/**
 * lotus added 2019.11.25
 * for sub class to override, returns YES if subclasses do the encode/decode else return NO
 * if retunrs YES the auto encoding/decoding will do nothing aboute the key
 * otherwise you should return NO to let the auto coding do the encoding/decoding
 *
 * for example: you should do encoding/decoding for structs yourself and return YES
 * or any other encoding/decoding you wish to implement your customer method
 */
-(BOOL)encodeKey:(NSString *)key withCoder:(NSCoder *)aCoder;
-(BOOL)decodeKey:(NSString *)key withCoder:(NSCoder *)aCoder;

@end

NS_ASSUME_NONNULL_END
