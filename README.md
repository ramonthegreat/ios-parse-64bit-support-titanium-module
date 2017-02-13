iOS 64bit Support Parse Module for Appcelerator Titanium
========================================================

How to Setup Parse Module in your project for Compiling
-------------------------------------------------------
1. Download com.ramonparse.module.iphone-1.0.zip and install it in your project. Please check the link on [How to install module in Titanium](http://docs.appcelerator.com/platform/latest/#!/guide/Using_a_Module)
2. Clone this repository somewhere in your computer.
3. Open "~/module/com.ramonparse.module/1.0/module.xconfig" and edit the line from "/Users/ramoncalimbas/Documents/Appcelerator_Studio_Workspace/ramonparse" to the FULL PATH of where you cloned this repository.
4. Run the APP.

How to Modify/Build Parse Module
--------------------------------
1. Clone this repository somewhere in your computer.
2. Open "module.xconfig" file and edit the line from "/Users/ramoncalimbas/Documents/Appcelerator_Studio_Workspace/ramonparse" to the FULL PATH of where you cloned this repository.
3. In titanium.xconfig set the right Titanium SDK version: TITANIUM_SDK_VERSION = 5.1.1.GA
4. From a terminal, go to the cloned directory and run the build.py script:
	cd /PATH/TO/WHERE/YOU/CLONED/THIS/REPOSITORY
	python build.py
5. If build is success, a zip module will be generated in your current directory and you may use that in your project.

To Initialize
-------------
    
```javascript
	var parse = require('com.ramonparse.module');
	parse.initParse({
		appId: 'YOUR PARSE APP ID', 
		clientKey: 'YOUR PARSE CLIENT KEY'
	});
```


Create a new object in the class of 'Game':
-------------------------------------------

```javascript
    parse.createObject('Game', {
    	name: 'My first game', 
    	level: 1
    }, function(data) {
       if(data.error) {
       		// error happened
       } else {
       		// use data.object -- it is just plain JSON
       }       
    });
```

Update an object: 
----------------

```javascript
	// NOTE: obj must have been retrieved from parse module (and later modified).
    parse.updateObject(obj, function(data) { 
      if(data.error) {

      } else {
     		// worked!
      } 
    });
```

Find an object: 
---------------
Using an array of conditions in which to filter them.  For example: 

```javascript
    // specifying _User targets the 'User' class in Parse.  If you want to specify your own class, no need for the _.
	parse.findObjects('_User', [
		{key: 'email', condition: '==', value: 'someemail@someemail.com'}
	], function(data) {
		if(data.error) {
			// error, probably with connection
			return;
		}

		if(data.results.length > 0) { 
			//You've got some results
		}
	});
```

Using multiple conditions:
```javascript
	parse.findObjects('Game', [
		{key: 'level', condition: '>=', value: 1}, 
		{key: 'level', condition: '<=', value: 5}, 
		{key: 'status', condition: '==', value: 'live'},
		{key: 'position', condition: 'orderby', value: 'asc'}
	], function(data) {  ... });

```
Save All Objects:
-----------------

```javascript
	// for example, this one starts with findObjects
	parse.findObjects('Test', [], function(data) {
	  var objectArray = data.results; 
	
	  // assuming there are at least 2 objects in the array
	  objectArray[0].key = 'Another value';
	  objectArray[1].key = 'Yet another value';
	  
	  // now you can save them all at the same time here
	  parse.saveAllObjects(objectArray, function(data) {
	    if(data.success) { // yay!
	
	    }
	  });
	}); 
```

Signup User:
------------

```javascript
	parse.signupUser({
		email: 'EMAIL ADDRESS', 
		password: 'PASSWORD', 
		username: 'USERNAME'
	}, function(data) {
        if(data.error) {

		} else {
			// use data.user
		}			              
	});
```

Login User:
-----------

```javascript
	parse.loginUser({
		username: username, 
		password: password
	}, function(data) {
		if(data.error) {
			...
		}
	});
```

Current User
------------

```
	parse.currentUser will refer to the current user, and null if there's not one.

	Also, you can use parse.refreshUser() to ensure parse.currentUser contains the latest user info.
```

Request Password Reset:
-----------------------

```javascript
	parse.requestPasswordReset({
		email: 'some@email.com'
	}); 

	A user with this email is assumed to exist.  You can check before making this call by using 

	parse.findObjects('_User', [
		{key: 'email', condition: '==', value: 'some@email.com'}
	], function(data) {
		if(data.results && data.results.length > 0) { // the user exists

		}
	});
```

Upload a File:
--------------
Files need to be attached to an object.  Please make sure to pass in an object that you retrieved from the parse module when making the assignment.  

```javascript
    parse.createFile({
      name: 'FILENAME'
      data: 'DATA', // can be imageview.image, for example
      attachmentInfo: {
        object: objectToAttachTo,  // this will have been retrieved from parse module, and can be parse.currentUser  
        key: 'KEY'  // the file will be referenced by this key inside of objectToAttachTo
      }
    }, function(data) {
    	if(data.error) { ... }
    });
```

Cloud Code:
-----------

```javascript
	parse.callCloudFunction('FUNCTION NAME', {
		PARAM1: 'VALUE1'  // your parameters here	
	}, function(result) {
		if(result.error) { // errror }
		else {
			// use result.object
		}
	});
```	
	
Push Notifications:
-------------------
For more info on Parse Push Notifications at setting up SSL push certificates : [https://parse.com/tutorials/ios-push-notifications](https://parse.com/tutorials/ios-push-notifications)

To register for push notifications unique token should be retrieved from the device.

```javascript
	Ti.Network.registerForPushNotifications({
		callback: function pushCallback(e)
		{},
		success: function pushSuccess(e)
		{
			deviceToken = e.deviceToken;
			parse.registerForPush(deviceToken, 'dummyChannel', function(data) {
				// output some data to check for success / errors
				// alert(data);
			});
		},
		error: function pushError(e)
		{
			// If unable to get deviceToken check for errors here
			// alert('Error!: '+JSON.stringify(e));
		},
		types: [
			Ti.Network.NOTIFICATION_TYPE_BADGE,
			Ti.Network.NOTIFICATION_TYPE_ALERT,
			Ti.Network.NOTIFICATION_TYPE_SOUND
		]
	});
```

Subscribing from channel:
-------------------------

```javascript
	parse.subscribeToChannel('dummyChannel', function(data) {
		// alert(data);
	});	
```

Unsubscribing from channel:
---------------------------

```javascript
	parse.unsubscribeToChannel('dummyChannel', function(data) {
		// alert(data);
	});
```
	
Clearing the app badge (reset to 0) and persist on server:
----------------------------------------------------------

```javascript
	parse.clearBadge();
```
	