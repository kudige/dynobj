# Dynobj

Dynobj implements a new class of objects that support dynamic __get__ and __set__ functions
for dynamic attributes (similar to languages like Python).

Usage:

<pre><code>
var DynObj = new (require('dynobj').DynObj)()
var MyCoolClass = DynObj.create()
MyCoolClass.prototype.__get__ = function(key) {
	return 'cool '+key
}

MyCoolClass.prototype.__set__ = function(key, val) {
    if (key === 'allowed')
	    return true // default behaviour

    // returning anything other that true will suppress the default behaviour and allows you you override
    console.log('someone tried to set '+key)
    return false
}
</code></pre>

## License 
As described in LICENSE
