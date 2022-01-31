void setBuildStatus(String message, String state) {
  step([
      $class: "GitHubCommitStatusSetter",
      reposSource: [$class: "ManuallyEnteredRepositorySource", url: "https://github.com/RemoteBoatX/-its_a_test-.git"],
      contextSource: [$class: "ManuallyEnteredCommitContextSource", context: "ci/jenkins/build-status"],
      errorHandlers: [[$class: "ChangingBuildStatusErrorHandler", result: "UNSTABLE"]],
      statusResultSource: [ $class: "ConditionalStatusResultSource", results: [[$class: "AnyBuildResult", message: message, state: state]] ]
  ]);
}


pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
               // Commands for build
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
