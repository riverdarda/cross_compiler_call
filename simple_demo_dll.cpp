#include "simple_demo.h"
#include <map>
#include <algorithm>


// Extern C
struct KVStore{
    std::map<std::string,std::string> m_;
};


extern "C"{
    HKVStore CALLING_CONVENTION Create_KVStore(){
        try{
            return new KVStore;
        }
        catch(std::exception&){
            return nullptr;
        }
    }

    void CALLING_CONVENTION Destroy_KVStore(HKVStore h){
        delete h;
    }

    error_code CALLING_CONVENTION Put (HKVStore h,const char* key, int32_t key_count,const char* value, int32_t value_count){
        try{
            std::string key(key,key_count);
            std::string value(value,value_count);
            h->m_[key] = value;
            return 0;
        }
        catch(std::exception&){
            return -1;
        }
    }
    error_code CALLING_CONVENTION Get(HKVStore h, const char* key, int32_t key_count,const char** pvalue,int32_t* pvalue_count,char* breturn){
        try{
            std::string key(key,key_count);
            auto iter = h->m_.find(key);
            if(iter == h->m_.end()){
                *breturn = 0;
                return 0;
            }
            else{
                std::string value = iter->second;
                auto pc = new char[value.size()];
                std::copy(value.begin(),value.end(),pc);
                *pvalue_count = value.size();
                *pvalue = pc;
                return 0;
            }
        }
        catch(std::exception&){
            return -1;
        }
    }
    error_code CALLING_CONVENTION Delete(HKVStore h, const char* key, int32_t key_count,char* breturn){
        try{
            std::string key(key,key_count);
            auto iter = h->m_.find(key);
            if(iter == h->m_.end()){
                *breturn = 0;
                return 0;
            }
            else{
                h->m_.erase(iter);
                return 0;
            }
        }
        catch(std::exception&){
            return -1;
        }
    }
}

// Compiler Vtable

struct KVStoreImplementation:public IKVStore{
    std::map<std::string,std::string> m_;

    virtual error_code CALLING_CONVENTION Put (const char* key, int32_t key_count,const char* value, int32_t value_count) override{
        try{
            std::string key(key,key_count);
            std::string value(value,value_count);
            m_[key] = value;
            return 0;
        }
        catch(std::exception&){
            return -1;
        }
    }
    virtual error_code CALLING_CONVENTION Get(const char* key, int32_t key_count,const char** pvalue,int32_t* pvalue_count,char* breturn) override{
        try{
            std::string key(key,key_count);
            auto iter = m_.find(key);
            if(iter == m_.end()){
                *breturn = 0;
                return 0;
            }
            else{
                std::string value = iter->second;
                auto pc = new char[value.size()];
                std::copy(value.begin(),value.end(),pc);
                *pvalue_count = value.size();
                *pvalue = pc;
                return 0;
            }
        }
        catch(std::exception&){
            return -1;
        }
    }

    virtual error_code CALLING_CONVENTION Delete(const char* key, int32_t key_count,char* breturn)override{
        try{
            std::string key(key,key_count);
            auto iter = m_.find(key);
            if(iter == m_.end()){
                *breturn = 0;
                return 0;
            }
            else{
                m_.erase(iter);
                return 0;
            }
        }
        catch(std::exception&){
            return -1;
        }
    }

    virtual void CALLING_CONVENTION Destroy() override {
        delete this;
    }
};

extern "C"{
    IKVStore* CALLING_CONVENTION Create_KVStoreImplementation(){
        try{
            return new KVStoreImplementation;
        }
        catch(std::exception&){
            return nullptr;
        }
    }
}

// Programmer generated vtable

struct KVStore2Implementation:public IKVStore2{
    std::map<std::string,std::string> m_;
    IKVStoreVtable vt;

    KVStore2Implementation(){
        vtable = &vt;
        vtable->Put = &Put_;
        vtable->Get = &Get_;
        vtable->Delete = &Delete_;
        vtable->Destroy = &Destroy_;
    }


    static void CALLING_CONVENTION Destroy_(IKVStore2* ikv ){
        delete static_cast<KVStore2Implementation*>(ikv);
    }

    static error_code CALLING_CONVENTION Put_ (IKVStore2* ikv, const char* key, int32_t key_count,const char* value, int32_t value_count){
        try{
            std::string key(key,key_count);
            std::string value(value,value_count);
            static_cast<KVStore2Implementation*>(ikv)->m_[key] = value;
            return 0;

        }
        catch(std::exception&){
            return -1;
        }
    }
    static error_code CALLING_CONVENTION Get_(IKVStore2* ikv,  const char* key, int32_t key_count,const char** pvalue,int32_t* pvalue_count,char* breturn){
        try{
            std::string key(key,key_count);
            auto iter = static_cast<KVStore2Implementation*>(ikv)->m_.find(key);
            if(iter == static_cast<KVStore2Implementation*>(ikv)->m_.end()){
                *breturn = 0;
                return 0;
            }
            else{
                std::string value = iter->second;
                auto pc = new char[value.size()];
                std::copy(value.begin(),value.end(),pc);
                *pvalue_count = value.size();
                *pvalue = pc;

                return 0;
            }

        }
        catch(std::exception&){
            return -1;
        }

    }
    static error_code CALLING_CONVENTION Delete_(IKVStore2* ikv,  const char* key, int32_t key_count,char* breturn){
        try{
            std::string key(key,key_count);
            auto iter = static_cast<KVStore2Implementation*>(ikv)->m_.find(key);
            if(iter == static_cast<KVStore2Implementation*>(ikv)->m_.end()){
                *breturn = 0;
                return 0;
            }
            else{
                static_cast<KVStore2Implementation*>(ikv)->m_.erase(iter);

                return 0;
            }

        }
        catch(std::exception&){
            return -1;
        }
    }



};

extern "C"{
    IKVStore2* CALLING_CONVENTION Create_KVStore2Implementation(){
        try{
            return new KVStore2Implementation;
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}

struct KVStore2Implementation2{
    std::map<std::string,std::string> m_;

    IKVStore2DerivedImplementation imp_;

    KVStore2Implementation2(){
        imp_.Put = [this](std::string key, std::string value){
            m_[key] = value;
        };
    }
};

extern "C"{
    IKVStore2* CALLING_CONVENTION Create_KVStore2Implementation2(){
        try{
           auto p =  new KVStore2Implementation2;
           return &p->imp_;
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}
struct KVStore2Implementation3{
    std::map<std::string,std::string> m_;

    IKVStore2DerivedImplementation2 imp_;

    KVStore2Implementation3(){
        imp_.Put = [this](std::string key, std::string value){
            m_[key] = value;
        };
    }
};

extern "C"{
    cross_compiler_interface::portable_base* CALLING_CONVENTION Create_KVStore2Implementation3(){
        try{
           auto p =  new KVStore2Implementation3;
           return &p->imp_;
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}

struct IKV_simple_cross_function3_implementation{
    std::map<std::string,std::string> m_;

    implement_interface<IKV_simple_cross_function3> imp_;

    IKV_simple_cross_function3_implementation(){
        imp_.Put = [this](std::string key, std::string value){
            m_[key] = value;
        };
    }
};

extern "C"{
    cross_compiler_interface::portable_base* CALLING_CONVENTION Create_IKV_simple_cross_function3_implementation(){
        try{
           auto p =  new IKV_simple_cross_function3_implementation;
           return p->imp_.get_portable_base();
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}
struct IKV_simple_cross_function4_implementation{
    std::map<std::string,std::string> m_;

    implement_interface<IKV_simple_cross_function4> imp_;

    IKV_simple_cross_function4_implementation(){
        imp_.Put = [this](std::string key, std::string value){
            m_[key] = value;
        };
    }
};

extern "C"{
    cross_compiler_interface::portable_base* CALLING_CONVENTION Create_IKV_simple_cross_function4_implementation(){
        try{
           auto p =  new IKV_simple_cross_function4_implementation;
           return p->imp_.get_portable_base();
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}
struct ImplementKVStore{
    cross_compiler_interface::implement_interface<InterfaceKVStore> imp_;

    std::map<std::string,std::string> m_;

    ImplementKVStore(){

        imp_.Put = [this](std::string key, std::string value){
            m_[key] = value;
        };

        imp_.Get = [this](std::string key, cross_compiler_interface::out<std::string> value)->bool{
            auto iter = m_.find(key);
            if(iter==m_.end()) return false;
            value.set(iter->second);
            return true;
        };

        imp_.Delete = [this](std::string key)->bool{
            auto iter = m_.find(key);
            if(iter==m_.end())return false;
            m_.erase(iter);
            return true;
        };
        
        imp_.Destroy = [this](){
            delete this;
        };
    }
};
extern "C"{
    cross_compiler_interface::portable_base* CALLING_CONVENTION Create_ImplementKVStore(){
        try{
            auto p = new ImplementKVStore;
            return p->imp_.get_portable_base();
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}


struct ImplementKVStore2
    :public cross_compiler_interface::implement_unknown_interfaces<ImplementKVStore2,InterfaceKVStore2>

{

    std::map<std::string,std::string> m_;

    ImplementKVStore2(){
        using cross_compiler_interface::cr_string;
        auto imp = get_implementation<InterfaceKVStore2>();

        imp->Put = [this](cr_string key, cr_string value){
            m_[key.to_string()] = value.to_string();
        };

        imp->Get = [this](cr_string key, cross_compiler_interface::out<std::string> value)
		->bool{
            auto iter = m_.find(key.to_string());
            if(iter==m_.end()) return false;
            value.set(iter->second);
            return true;
        };

        imp->Delete = [this](cr_string key)->bool{
            auto iter = m_.find(key.to_string());
            if(iter==m_.end())return false;
            m_.erase(iter);
            return true;
        };

    }


};
extern "C"{
    cross_compiler_interface::portable_base* CALLING_CONVENTION Create_ImplementKVStore2(){
        try{
            auto p = ImplementKVStore2::create();
            return p.get_portable_base_addref();
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}



struct PropertyInterfaceImplementationHelper{

    std::map<std::string, std::string> m_;

    PropertyInterfaceImplementationHelper(cross_compiler_interface::implement_interface<PropertyInterface>& imp){
        imp.SetProperty = [this](std::string key, std::string value){
            m_[key] = value;
        };

        imp.GetProperty = [this](std::string key, std::string default_value){
            auto iter = m_.find(key);
            if(iter==m_.end()) return default_value;
            return iter->second;
        };


    };
};


struct ImplementPropertyInterface{
    
    cross_compiler_interface::implement_interface<PropertyInterface> imp_;

    PropertyInterfaceImplementationHelper helper_;

    ImplementPropertyInterface():helper_(imp_){}

};


struct ImplementPropertyInterfaceBinary{

    cross_compiler_interface::module m_;

    cross_compiler_interface::use_interface<PropertyInterface> other_;

    cross_compiler_interface::implement_interface<PropertyInterface> imp_;

    ImplementPropertyInterfaceBinary()
        :m_("AwesomeDll")
    {
        other_ = cross_compiler_interface::create<PropertyInterface>(m_,"CreatePropertyManager");

        imp_.set_runtime_parent(other_);
    }
};


struct ImplementKVStoreFinal
    :public cross_compiler_interface::implement_unknown_interfaces<ImplementKVStoreFinal,KVStoreFinal::Interface>{

            typedef cross_compiler_interface::cr_string cr_string;

            std::map<std::string,std::string> m_;

            void Put(cr_string key, cr_string value){
                m_[key.to_string()] = value.to_string();

            }

            bool Get(cr_string key, cross_compiler_interface::out<std::string> pvalue){
                auto iter = m_.find(key.to_string());
                if(iter==m_.end()) return false;
                pvalue.set(iter->second);
                return true;
            }

            bool Delete(cr_string key){
                auto iter = m_.find(key.to_string());
                if(iter==m_.end())return false;
                m_.erase(iter);
                return true;
            }


            ImplementKVStoreFinal(){
                get_implementation<KVStoreFinal::Interface>()->map_to_member_functions_no_prefix(this);
            }
};

extern "C"{
    cross_compiler_interface::portable_base* CALLING_CONVENTION Create_ImplementKVStoreFinal(){
        try{
            auto p = ImplementKVStoreFinal::create();
            return p.get_portable_base_addref();
        }
        catch(std::exception&){
            return nullptr;
        }

    }

}