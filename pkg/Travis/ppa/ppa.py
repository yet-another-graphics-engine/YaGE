import subprocess
import os

CHANGELOG_FORMAT = '''yage (0.1.0~{date}+0800~{gitrev}~ubuntu{ubuntu_version}ppa1) {codename}; urgency=low

  * {commit_message}

 -- {commit_info}
'''

UBUNTU_RELEASES = [['precise', '12.04'],  # until 2017-04-26
                   ['trusty',  '14.04'],  # until 2019-04
                   ['vivid',   '15.04'],  # until 2016-01
                   ['wily',    '15.10']]  # until 2016-07

if __name__ == '__main__':
    universal_info = {}
    universal_info['gitrev'] = subprocess.check_output('git rev-parse --short HEAD', shell=True)[:-1]
    universal_info['commit_message'] = subprocess.check_output('git log HEAD -1 --format=%s', shell=True)[:-1]
    universal_info['commit_info'] = subprocess.check_output("git log HEAD -1 --format='%cn <%ce>  %aD'", shell=True)[:-1]
    universal_info['date'] = subprocess.check_output('TZ=Asia/Shanghai date +%Y%m%d.%H%M --date=@`git log HEAD -1 --format=%ct`', shell=True)[:-1]
    for ubuntu_release in UBUNTU_RELEASES:
        os.makedirs('build/%s' % ubuntu_release[0])
        os.system('cp -r debian build/%s/' % ubuntu_release[0])
        ppa_info = universal_info.copy()
        ppa_info['codename'] = ubuntu_release[0]        # like precise
        ppa_info['ubuntu_version'] = ubuntu_release[1]  # like 12.04
        with open('build/%s/debian/changelog' % ubuntu_release[0], 'wb') as changelog_file:
            changelog_file.write(CHANGELOG_FORMAT.format(**ppa_info))