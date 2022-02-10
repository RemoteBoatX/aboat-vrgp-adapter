void setBuildStatus(String message, String state) {
    step([
        $class: "GitHubCommitStatusSetter",
        reposSource: [$class: "ManuallyEnteredRepositorySource", url: "https://github.com/RemoteBoatX/aboat-vrgp-adapter.git"],
        contextSource: [$class: "ManuallyEnteredCommitContextSource", context: "ci/jenkins/build-status"],
        errorHandlers: [[$class: "ChangingBuildStatusErrorHandler", result: "UNSTABLE"]],
        statusResultSource: [ $class: "ConditionalStatusResultSource", results: [[$class: "AnyBuildResult", message: message, state: state]] ]
    ]);
}

// node {
//     checkout scm

//     def dockerfile = "Dockerfile.amd64"
//     def dockerImage = docker.build("remoteboatx/aboat-vrgp-adapter:latest", "-f ${dockerfile} .")
// }

pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                script {
                    dockerImage = docker.build -f Dockerfile.amd64 --tag="remoteboatx/aboat-vrgp-adapter:latest" .
                }
            }
        }

        stage('Test') {
            steps {
                // Commands for testing
            }
        }
        stage('Deploy'){
            steps{
                script{
                    if(env.BRANCH_NAME == 'main'){
                        //Commands for deployment (only in main)
                    }
                }
            }
        }
    }

    post {
        success {
            setBuildStatus("Build succeeded", "SUCCESS");
        }
        failure {
            setBuildStatus("Build failed", "FAILURE");
        }
    }
}
