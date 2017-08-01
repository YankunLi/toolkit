#include <iostream>
#include <string>
#include <assert.h>    
#include <leveldb/db.h>
#include <leveldb/write_batch.h>

using namespace std;

int main(void) 
{       

    leveldb::DB      *db;    
    leveldb::Options  options;    
    options.create_if_missing = true;

    // open A leveldb database has a name which corresponds to a file system directory
    leveldb::Status status = leveldb::DB::Open(options,"/tmp/testdb", &db);    
    assert(status.ok());    

    string key = "liyankun";    
    string value = "handsome";    

    // write
    status = db->Put(leveldb::WriteOptions(), key, value);  
    assert(status.ok());

    // read
    status = db->Get(leveldb::ReadOptions(), key, &value);    
    assert(status.ok());    

    cout<<value<<endl;    

    // delete
//    status = db->Delete(leveldb::WriteOptions(), key);    
//    assert(status.ok());
   
    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
    for ( it->SeekToFirst(); it->Valid(); it->Next() ){
        cout << it->key().ToString() << ":" << it->value().ToString() <<endl;
    }
    assert(it->status().ok());
    delete it;

    status = db->Get(leveldb::ReadOptions(),key, &value);    
    if(!status.ok()) {
        cerr<<key<<"    "<<status.ToString()<<endl;
    } else {
        cout<<key<<"==="<<value<<endl;    
    }   

    //The following variation shows how to process just the keys in the range [start,limit): 
    /*for (it->Seek(start);
       it->Valid() && it->key().ToString() < limit;
       it->Next()) {
    ...
    }*/

    //You can also process entries in reverse order. (Caveat: reverse iteration may be somewhat slower than forward iteration.) 
    /*for (it->SeekToLast(); it->Valid(); it->Prev()) {
    ...
    }*/

    //atomic updates
    std::string key1 = "liyankun";
    std::string key2 = "yankunli";
    status = db->Get(leveldb::ReadOptions(), key1, &value);
    if(status.ok()){
        cout << "start atomic updates" << endl;
        leveldb::WriteBatch batch;
        batch.Delete(key1);
        batch.Put(key2, value);
        status = db->Write(leveldb::WriteOptions(), &batch);
        assert(status.ok());
    }

    //synchronous Write
    leveldb::WriteOptions write_options;
    write_options.sync = true;
    status = db->Put(write_options, key, value);
    assert(status.ok());

    // close
    delete db;

    return 0;   
}
