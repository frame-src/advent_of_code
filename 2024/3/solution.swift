import Foundation

func readFileContent(from fileName: String, at directoryPath: String) -> String {
    let fileManager = FileManager.default

    if fileManager.fileExists(atPath: directoryPath) {
        let directoryURL = URL(fileURLWithPath: directoryPath) 
        let fileURL = directoryURL.appendingPathComponent(fileName)
        do { 
            let fileContents = try String(contentsOf: fileURL, encoding: .utf8)
            return fileContents
        } catch {
            return "Error reading file: \(error)"
        }
    } else {
        return "Failed to find directory: \(directoryPath)"
    }
}

func splitContent(input: String) -> [String] {
    let lines = input.split(separator:"\n").map{String($0)}
    return lines
}

func findNumbers(text: String) -> Int {
    let pattern = #"mul\((\d+),(\d+)\)"#

    let regex = try! NSRegularExpression(pattern: pattern)
    let matches = regex.matches(in: text, range: NSRange(text.startIndex..., in: text))
    var result : Int = 0

    for match in matches{
        let firstRange = Range(match.range(at: 1), in: text)!
        let secondRange = Range(match.range(at: 2), in: text)!
        let firstInteger = text[firstRange]
        let secondInteger = text[secondRange]
        if let firstInt = Int(firstInteger), let secondInt = Int(secondInteger) {
            result += firstInt * secondInt
        }
    }
    return result
}


func processLine(lines: [String]) -> Int {
    var result : Int = 0

    for line in lines {
        result = result + findNumbers(text : line)
    }
    return result
}

func main() {
    let fileName = "input"
    let fileManager = FileManager.default
    let currentDirectoryPath = fileManager.currentDirectoryPath
    var content : String = ""
    content = readFileContent(from: fileName, at: currentDirectoryPath)

    let lines = splitContent( input:content )
    let result = processLine(lines: lines)
    print(result)
}

main()
