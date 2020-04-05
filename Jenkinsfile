#!/usr/bin/env groovy

pipeline
{
	agent
	{
		dockerfile
		{
			filename "tools/jenkins/debian.dockerfile"
			// The source path should be replaced by an environment variable
			args "-v /volume1/docker/jenkins/cache:/cache"
		}
	}
	stages
	{
		stage("Info")
		{
			steps
			{
				sh "bazel --version"
				sh "g++ --version"
				sh "python --version"
			}
		}
		/**
		 * Parallelized tests are done here
		 */
		stage("Tests")
		{
			parallel
			{
				stage("bazel test ...")
				{
					steps
					{
						sh "bazel --output_user_root=/cache/output test ... --disk_cache=/cache/bazel -s" 
					}
				}
			}
		}
	}
}
