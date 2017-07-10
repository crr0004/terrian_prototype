#Having multiple lua scripts

Each script needs it's own set of globals
Each time a script is loaded, it's globals need to be re-set
	including each instance, not just file
How do we identity a script?
	Entry in the registry?
	Array of scripts?
	Hashset or hashmap?
	Probably use hashmap so we can wrap each script. Can also pair each of the
	rendering queues in there.
