#ifndef EvaLLVM_h
#define EvaLLVM_h

#import <iostream>
#import <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

class EvaLLVM {
public:
    // constructor
    EvaLLVM() {
        context = std::make_unique<llvm::LLVMContext>();
        module = std::make_unique<llvm::Module>("EvaLLVM", *context);
        builder = std::make_unique<llvm::IRBuilder<>>(*context);
        // external functions
        setupExternalFunctions();
    }
    // execute program
    void exec(const std::string& program) {
        // TODO parse to AST
        
        // compile
        compile();

        // print generated code
        module->print(llvm::outs(), nullptr);
        std::cout << "\n";

        // save to file out.ll
        saveModuleToFile("out.ll");
    }
private:
    // compile expression
    void compile(/* TODO ast */) {
        // create main function
        fn = createFunction(
            // name
            "main",
            // type
            llvm::FunctionType::get(
                // return type
                builder->getInt32Ty(),
                // args
                false
            )
        );

        // compile main body
        gen(/* TODO ast */);

        // test only : create return instruction
        // auto i32Result = builder->CreateIntCast(
        //     // value
        //     result,
        //     // type
        //     builder->getInt32Ty(),
        //     // isSigned
        //     true
        // );
        builder->CreateRet(builder->getInt32(0));
    }

    // main compile loop
    llvm::Value* gen(/* TODO ast */) {
        // return builder->getInt32(42);
        auto str = builder->CreateGlobalStringPtr("hello llvm\n");
        // printf
        auto printfFn = module->getFunction("printf");
        // args
        std::vector<llvm::Value*> args;

        return builder->CreateCall(printfFn, str);
    }

    // declare external functions
    void setupExternalFunctions() {
        // int printf(char* format, ...)
        module->getOrInsertFunction(
            // name
            "printf",
            // type
            llvm::FunctionType::get(
                // return type
                builder->getInt32Ty(),
                // args
                {
                    builder->getInt8PtrTy()
                },
                // isVarArg
                true
            )
        );

    }

    // create function
    llvm::Function* createFunction(const std::string& fnName, llvm::FunctionType* fnType) {
        // function prototype (if defined)
        auto fn = module->getFunction(fnName);
        if (fn == nullptr) {
            fn = llvm::Function::Create(
                // type
                fnType,
                // linkage
                llvm::Function::ExternalLinkage,
                // name
                fnName,
                // module
                *module
            );
            // check for errors
            verifyFunction(*fn);
        }
        // entry block
        auto entry = llvm::BasicBlock::Create(*context, "entry", fn);
        builder->SetInsertPoint(entry); // set builder to entry block

        return fn;
    }

    // save module to file
    void saveModuleToFile(const std::string& filename) {
        std::error_code error;
        llvm::raw_fd_ostream outLL(filename, error);
        module->print(outLL, nullptr);
    }

    // LLVM function
    llvm::Function* fn;
    // LLVM context
    std::unique_ptr<llvm::LLVMContext> context;
    // LLVM module
    std::unique_ptr<llvm::Module> module;
    // LLVM builder
    std::unique_ptr<llvm::IRBuilder<>> builder;
};

#endif